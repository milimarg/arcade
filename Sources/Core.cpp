/*
** EPITECH PROJECT, 2024
** arcade-preparations
** File description:
** Core
*/

#include "Core.hpp"

namespace arcade
{
    Core::Core(std::string &graphical)
        :
        _graphicalLibrary(nullptr),
        _gameLibrary(nullptr),
        _graphicalModule(nullptr),
        _gameModule(nullptr),
        _gameIndex(0),
        _graphicalIndex(0),
        _indexMainMenu(0),
        _eventWrapper(nullptr),
        _windowWrapper(nullptr),
        _secretKey("ufmiaoudeadbeefmiaoudeadbeef!!!!"),
        _currentUserName(),
        _currentScore(0)
    {
        initLib(graphical);
    }

    Core::~Core()
    {
        shutdown();
    }

    bool Core::areSameFiles(const std::string& first, const std::string& second)
    {
        std::ifstream one(first, std::ios::binary | std::ios::ate);
        std::ifstream two(second, std::ios::binary | std::ios::ate);

        if (!one.is_open() || !two.is_open())
            return false;
        if (one.tellg() != two.tellg())
            return false;
        one.seekg(0, std::ios::beg);
        two.seekg(0, std::ios::beg);
        return std::equal(std::istreambuf_iterator<char>(one.rdbuf()), std::istreambuf_iterator<char>(), std::istreambuf_iterator<char>(two.rdbuf()));
    }

    void Core::initLib(std::string &graphical)
    {
        std::filesystem::path lib = "./lib/";
        std::ifstream file;

        file.open(graphical);
        if (!file)
            throw arcade::Error("This lib doesn't exist");
        if (std::filesystem::exists(lib) && std::filesystem::is_directory(lib)) {
            for (const auto &entry : std::filesystem::directory_iterator(lib)) {
                std::string filepath = "./lib/" + entry.path().filename().string();
                try {
                    std::unique_ptr<LibraryHandler> newLib = std::move(std::make_unique<LibraryHandler>(filepath));
                    std::string type = newLib->getSymbol<std::string>("getType");
                    newLib->close();
                    if (type == "game") {
                        addGameLibrary(filepath);
                        continue;
                    }
                    if (type == "graphical") {
                        addGraphicalLibrary(filepath);
                        if (areSameFiles(filepath, graphical))
                            _graphicalIndex = _graphicalLibraryList.size() - 1;
                        continue;
                    }
                    if (type == "mainMenu") {
                        addGameLibrary(filepath);
                        _gameIndex = _gameLibraryList.size() - 1;
                        _indexMainMenu = _gameIndex;
                        continue;
                    }
                } catch (const std::exception& e) {
                    throw arcade::Error(e.what());
                }
                throw arcade::Error("Core - initLib - " + filepath + " have no type.");
            }
        } else
            throw arcade::Error("Core - initLib - ./lib doesn't exist.");
        if (_graphicalLibraryList.size() == 0 || _gameLibraryList.size() == 0)
            throw arcade::Error("Core - initLib - No graphicals or games lib.");
        try {
            _gameLibrary = std::move(std::make_unique<LibraryHandler>(_gameLibraryList[_gameIndex]));
            _graphicalLibrary = std::move(std::make_unique<LibraryHandler>(_graphicalLibraryList[_graphicalIndex]));
        } catch (const std::exception& e) {
            throw arcade::Error(e.what());
        }
    }

    bool Core::initialize()
    {
        if (!_graphicalLibrary->isOpen() || !_gameLibrary->isOpen())
            throw arcade::Error("Core - initialize - Failed to open one or more libraries.");
        if (!loadGameModule() || !loadGraphicalModule())
            throw arcade::Error("Core - initialize - Failed to load modules.");
        return true;
    }

    void Core::initializeModules()
    {
        if (!_graphicalLibrary->isOpen() || !_gameLibrary->isOpen())
            throw arcade::Error("Core - initializeModules - Failed to open one or more libraries.");
        if (!loadGameModule() || !loadGraphicalModule())
            throw arcade::Error("Core - initializeModules - Failed to load modules.");
    }

    void Core::initializeWrappers()
    {
        if (!_graphicalModule || !_gameModule)
            throw arcade::Error("Core - initializeWrappers - Graphical or game module not loaded.");

        try {
            _gameModule->init();
            _graphicalModule->init();
            _eventWrapper = _graphicalModule->getEventWrapper();
            _windowWrapper = _graphicalModule->getWindowWrapper();
        } catch (const std::exception& e) {
            throw arcade::Error(e.what());
        }


        if (!_eventWrapper || !_windowWrapper)
            throw arcade::Error("Core - initializeWrappers - Failed to retrieve one of the wrappers.");
    }

    int Core::updateModules()
    {
        try {
            _graphicalModule->pollEvents();

            _eventWrapper = _graphicalModule->getEventWrapper();

            if (_gameIndex % _gameLibraryList.size() == _indexMainMenu) {
                _gameModule->getTextsWrapper()->updateTextMap({{{0, 0}, Text(_graphicalLibraryList[_graphicalIndex])}});
                _currentUserName = _gameModule->getName();
            }

            _gameModule->applyEvents(_eventWrapper);

            if (handleChangeEvent() == 1)
                return 1;
            if (!_windowWrapper->isOpen())
                return -1;

            _gameModule->update(_time.getDeltaTime());
            _currentScore = std::max(_gameModule->getScore(), _currentScore);
        } catch (const std::exception& e) {
            throw arcade::Error(e.what());
        }
        return 0;
    }

    void Core::run()
    {
        int frameTime = 1000 / 60;
        int value = 0;

        initializeWrappers();

        try {
            while (_windowWrapper->isOpen()) {
                auto startTime = std::chrono::steady_clock::now();

                _time.update();

                value = updateModules();
                if (value == -1)
                    break;
                if (value == 1)
                    continue;

                _gameModule->draw(_graphicalModule.get());

                auto endTime = std::chrono::steady_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

                if (elapsedTime < frameTime)
                    std::this_thread::sleep_for(std::chrono::milliseconds(frameTime - elapsedTime));
            }

            _gameModule->stop();
            _graphicalModule->stop();
        } catch (const std::exception& e) {
            throw arcade::Error(e.what());
        }
    }

    void Core::shutdown()
    {
    }

    void Core::addGameLibrary(const std::string &libraryName)
    {
        _gameLibraryList.push_back(libraryName);
    }

    void Core::addGraphicalLibrary(const std::string &libraryName)
    {
        _graphicalLibraryList.push_back(libraryName);
    }

    bool Core::loadGameModule()
    {
        _gameModule.release();

        try {
            _gameModule = std::move(_gameLibrary->getSymbol<std::unique_ptr<IGameModule>>("entryPoint"));
        } catch (const std::exception& e) {
            throw arcade::Error(e.what());
        }
        if (!_gameModule)
            throw arcade::Error("Core - loadGameModule - Failed to load game module from library.");

        return true;
    }

    bool Core::loadGraphicalModule()
    {
        _graphicalModule.release();

        try {
            _graphicalModule = std::move(_graphicalLibrary->getSymbol<std::unique_ptr<IGraphicalModule>>("entryPoint"));
        } catch (const std::exception& e) {
            throw arcade::Error(e.what());
        }
        if (!_graphicalModule)
            throw arcade::Error("Core - loadGameModule - Failed to load graphical module from library.");

        return true;
    }

    int Core::handleChangeEvent()
    {
        ChangeKey tempChangeKey = ChangeKey::CHANGE_LIST_END;
        size_t index = 0;
        int returnValue = 0;
        std::vector<ChangeKey> keyList;

        while (1) {
            try {
                std::unique_ptr<IEventInfo> tempEventInfo = _eventWrapper->getChangeEvent();
                if (!tempEventInfo)
                    break;
                tempChangeKey = tempEventInfo->getChangeKey();
            } catch (const std::exception& e) {
                throw arcade::Error(e.what());
            }
            if (tempChangeKey == ChangeKey::CHANGE_LIST_END || tempChangeKey == ChangeKey::NONE)
                break;
            keyList.push_back(tempChangeKey);
        }

        for (auto &changeKey : keyList) {
            switch (changeKey) {
                case ChangeKey::PREV_GRAPHICAL_LIB:
                    if (_graphicalLibraryList.size() == 0)
                        break;
                    _graphicalIndex = (_graphicalIndex > 0) ? _graphicalIndex - 1 : _graphicalLibraryList.size() - 1;
                    index = _graphicalIndex % _graphicalLibraryList.size();
                    switchGraphicalLibrary(_graphicalLibraryList[index], true);
                    returnValue = 1;
                    break;
                case ChangeKey::NEXT_GRAPHICAL_LIB:
                    if (_graphicalLibraryList.size() == 0)
                        break;
                    _graphicalIndex = (_graphicalIndex < _graphicalLibraryList.size() - 1) ? _graphicalIndex + 1 : 0;
                    index = _graphicalIndex % _graphicalLibraryList.size();
                    switchGraphicalLibrary(_graphicalLibraryList[index], true);
                    returnValue = 1;
                    break;
                case ChangeKey::PREV_GAME_LIB:
                    if (_gameLibraryList.size() == 0)
                        break;
                    if (_gameIndex % _gameLibraryList.size() != _indexMainMenu)
                        saveCurrentScore(_gameLibraryList[_gameIndex % _gameLibraryList.size()]);
                    if (_gameIndex < 0)
                        _gameIndex = _gameLibraryList.size() - 1;
                    else
                        _gameIndex = (_gameIndex > 0) ? _gameIndex - 1 : _gameLibraryList.size() - 1;
                    index = _gameIndex % _gameLibraryList.size();
                    switchGameLibrary(_gameLibraryList[index], true);
                    returnValue = 1;
                    break;
                case ChangeKey::NEXT_GAME_LIB:
                    if (_gameLibraryList.size() == 0)
                        break;
                    if (_gameIndex % _gameLibraryList.size() != _indexMainMenu)
                        saveCurrentScore(_gameLibraryList[_gameIndex % _gameLibraryList.size()]);
                    if (_gameIndex < 0)
                        _gameIndex = 0;
                    else
                        _gameIndex = (_gameIndex < _gameLibraryList.size() - 1) ? _gameIndex + 1 : 0;
                    index = _gameIndex % _gameLibraryList.size();
                    switchGameLibrary(_gameLibraryList[index], true);
                    returnValue = 1;
                    break;
                case ChangeKey::MAIN_MENU:
                    if (_gameIndex % _gameLibraryList.size() != _indexMainMenu)
                        saveCurrentScore(_gameLibraryList[_gameIndex % _gameLibraryList.size()]);
                    switchMainMenu(true);
                    returnValue = 1;
                    break;
                case ChangeKey::ESCAPE:
                    if (_gameIndex % _gameLibraryList.size() != _indexMainMenu)
                        saveCurrentScore(_gameLibraryList[_gameIndex % _gameLibraryList.size()]);
                    _windowWrapper->closeWindow();
                    break;
                default:
                    break;
            }
        }

        return returnValue;
    }

    std::string Core::cleanLibName(const std::string &libName)
    {
        std::string cleanedName = libName;

        if (cleanedName.substr(0, 6) == "./lib/")
            cleanedName.erase(0, 6);
        if (cleanedName.substr(0, 7) == "arcade_")
            cleanedName.erase(0, 7);
        if (cleanedName.size() > 3 && cleanedName.substr(cleanedName.size() - 3) == ".so")
            cleanedName.erase(cleanedName.size() - 3);
        return cleanedName;
    }

    void Core::saveCurrentScore(const std::string &libName)
    {
        if (_currentScore == 0)
            return;
        std::string name = cleanLibName(libName);
        std::filesystem::path scoresDir = "./Scores/";

        if (!std::filesystem::exists(scoresDir)) {
            if (!std::filesystem::create_directory(scoresDir))
                throw arcade::Error("Core - saveCurrentScore - Failed to create scores directory.");
        }

        std::string scoresFilePath = scoresDir.string() + name + ".abs";
        std::ifstream scoresFileIn(scoresFilePath, std::ios::binary);
        if (!scoresFileIn.is_open()) {
            std::ofstream newScoresFile(scoresFilePath, std::ios::binary);
            if (!newScoresFile.is_open())
                throw arcade::Error("Core - saveCurrentScore - Failed to create score file.");
            newScoresFile.close();
            scoresFileIn.open(scoresFilePath, std::ios::binary);
            if (!scoresFileIn.is_open())
                throw arcade::Error("Core - saveCurrentScore - Failed to open score file.");
        }

        std::stringstream fileContent;
        fileContent << scoresFileIn.rdbuf();
        scoresFileIn.close();

        std::string decryptedContent = decryptData(fileContent.str(), _secretKey);
        std::string scoreString = _currentUserName + ": " + std::to_string(_currentScore);
        decryptedContent += scoreString + '\n';
        std::string encryptedContent = encryptData(decryptedContent, _secretKey);

        std::ofstream scoresFileOut(scoresFilePath, std::ios::binary);
        if (!scoresFileOut.is_open())
            throw arcade::Error("Core - saveCurrentScore - Failed to open score file for writing.");
        scoresFileOut << encryptedContent;
        scoresFileOut.close();

        _currentScore = 0;
    }

    void Core::switchGameLibrary(const std::string &path, bool inGame)
    {
        if (std::find(_gameLibraryList.begin(), _gameLibraryList.end(), path) == _gameLibraryList.end())
            throw arcade::Error("Core - switchGameLibrary - Failed to switch game library.");

        try {
            if (inGame && _gameModule)
                _gameModule->stop();

            _gameLibrary->close();
            _gameLibrary.release();
            _gameLibrary = std::move(std::make_unique<LibraryHandler>(path));

            _gameModule.release();
            _gameModule = std::move(_gameLibrary->getSymbol<std::unique_ptr<IGameModule>>("entryPoint"));
            _gameModule->init();
        } catch (const std::exception& e) {
            throw arcade::Error(e.what());
        }
    }

    void Core::switchGraphicalLibrary(const std::string &path, bool inGame)
    {
        if (std::find(_graphicalLibraryList.begin(), _graphicalLibraryList.end(), path) == _graphicalLibraryList.end())
            throw arcade::Error("Core - switchGraphicalLibrary - Failed to switch graphical library.");

        try {
            if (inGame && _graphicalModule)
                _graphicalModule->stop();

            _graphicalLibrary->close();
            _graphicalLibrary.release();
            _graphicalLibrary = std::move(std::make_unique<LibraryHandler>(path));

            _graphicalModule.release();
            _graphicalModule = std::move(_graphicalLibrary->getSymbol<std::unique_ptr<IGraphicalModule>>("entryPoint"));
            _graphicalModule->init();

            if (inGame) {
                _eventWrapper = _graphicalModule->getEventWrapper();
                _windowWrapper = _graphicalModule->getWindowWrapper();
            }
        } catch (const std::exception& e) {
            throw arcade::Error(e.what());
        }
    }

    void Core::switchMainMenu(bool inGame)
    {
        _gameIndex = _indexMainMenu;

        try {
            if (inGame && _gameModule)
                _gameModule->stop();

            _gameLibrary->close();
            _gameLibrary.release();
            _gameLibrary = std::move(std::make_unique<LibraryHandler>(_gameLibraryList[_gameIndex]));

            _gameModule.release();
            _gameModule = std::move(_gameLibrary->getSymbol<std::unique_ptr<IGameModule>>("entryPoint"));
            _gameModule->init();
        } catch (const std::exception& e) {
            throw arcade::Error(e.what());
        }
    }

    std::string Core::encryptData(const std::string &plaintext, const std::string &key)
    {
        OpenSSL_add_all_algorithms();
        ERR_load_crypto_strings();

        const EVP_CIPHER *cipher = EVP_aes_256_cbc();
        const int keyLength = EVP_CIPHER_key_length(cipher);
        const int ivLength = EVP_CIPHER_iv_length(cipher);

        std::vector<unsigned char> iv(ivLength);
        RAND_bytes(iv.data(), ivLength);
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
        EVP_EncryptInit_ex(ctx, cipher, nullptr, reinterpret_cast<const unsigned char *>(key.c_str()), iv.data());
        int cipherTextLen = plaintext.length() + EVP_CIPHER_block_size(cipher);
        std::vector<unsigned char> cipherText(cipherTextLen);
        int len = 0;
        EVP_EncryptUpdate(ctx, cipherText.data(), &len, reinterpret_cast<const unsigned char *>(plaintext.c_str()), plaintext.length());
        cipherTextLen = len;
        EVP_EncryptFinal_ex(ctx, cipherText.data() + len, &len);
        cipherTextLen += len;
        EVP_CIPHER_CTX_free(ctx);
        std::string result(reinterpret_cast<char*>(iv.data()), iv.size());
        result += std::string(reinterpret_cast<char*>(cipherText.data()), cipherTextLen);
        return result;
    }

    std::string Core::decryptData(const std::string &ciphertext, const std::string &key)
    {
        OpenSSL_add_all_algorithms();
        ERR_load_crypto_strings();

        const EVP_CIPHER *cipher = EVP_aes_256_cbc();
        const int keyLength = EVP_CIPHER_key_length(cipher);
        const int ivLength = EVP_CIPHER_iv_length(cipher);

        std::string ivStr = ciphertext.substr(0, ivLength);
        std::vector<unsigned char> iv(ivStr.begin(), ivStr.end());
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
        EVP_DecryptInit_ex(ctx, cipher, nullptr, reinterpret_cast<const unsigned char *>(key.c_str()), iv.data());
        int plainTextLen = ciphertext.length() - ivLength + EVP_CIPHER_block_size(cipher);
        std::vector<unsigned char> plainText(plainTextLen);
        int len = 0;
        EVP_DecryptUpdate(ctx, plainText.data(), &len, reinterpret_cast<const unsigned char *>(ciphertext.c_str() + ivLength), ciphertext.length() - ivLength);
        plainTextLen = len;
        EVP_DecryptFinal_ex(ctx, plainText.data() + len, &len);
        plainTextLen += len;
        EVP_CIPHER_CTX_free(ctx);
        return std::string(reinterpret_cast<char*>(plainText.data()), plainTextLen);
    }
}
