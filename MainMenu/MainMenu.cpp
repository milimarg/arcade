/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** MainMenu
*/

#include "MainMenu.hpp"

namespace arcade
{
    MainMenu::MainMenu() :
        AGameModule("MainMenu"),
        _nameInput(""),
        _nameInputActive(false),
        _gameLibraries(),
        _graphicLibraries(),
        _selectedGameIndex(0),
        _selectedGraphicIndex(0),
        _mainMenuIndex(0),
        _isGameListChecked(true),
        _currentGraphical(),
        _secretKey("ufmiaoudeadbeefmiaoudeadbeef!!!!"),
        _scores({})
    {
    }

    MainMenu::~MainMenu()
    {
    }

    std::string MainMenu::cleanLibName(const std::string &libName)
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

    void MainMenu::initLibs()
    {
        std::filesystem::path lib = "./lib/";

        if (std::filesystem::exists(lib) && std::filesystem::is_directory(lib)) {
            for (const auto &entry : std::filesystem::directory_iterator(lib)) {
                std::string filename = entry.path().filename().string();
                std::string filepath = "./lib/" + filename;
                std::unique_ptr<LibraryHandler> newLib = std::make_unique<LibraryHandler>(filepath);
                std::string type = newLib->getSymbol<std::string>("getType");
                newLib->close();

                filename = cleanLibName(filename);
                if (type == "game") {
                    _gameLibraries.push_back(filename);
                    continue;
                }
                if (type == "graphical") {
                    _graphicLibraries.push_back(filename);
                    continue;
                }
                if (type == "mainMenu") {
                    _mainMenuIndex = _gameLibraries.size();
                    continue;
                }
            }
        } else
            throw arcade::Error("MainMenu - initLibs - ./lib doesn't exist.");
        if (_gameLibraries.size() == 0 || _graphicLibraries.size() == 0)
            throw arcade::Error("MainMenu - initLibs - No graphicals or games lib.");
    }

    void MainMenu::init()
    {
        createPixelsObject();
        createTextsObject();

        initLibs();
        loadScores();
    }

    void MainMenu::loadScores()
    {
        std::filesystem::path scoresDir = "./Scores/";

        if (!std::filesystem::exists(scoresDir))
            return;

        for (const auto &libName : _gameLibraries) {
            std::string scoresFilePath = scoresDir.string() + libName + ".abs";

            std::ifstream scoresFileIn(scoresFilePath, std::ios::binary);
            if (!scoresFileIn.is_open())
                continue;

            std::stringstream fileContent;
            fileContent << scoresFileIn.rdbuf();
            scoresFileIn.close();

            std::string decryptedContent = decryptData(fileContent.str(), _secretKey);

            std::stringstream decryptedStream(decryptedContent);
            std::string line;
            while (std::getline(decryptedStream, line)) {
                Score score = parseScore(line);
                if (score.getPlayerName() != "")
                    _scores[libName].push_back(score);
            }
        }
    }

    Score MainMenu::parseScore(const std::string &line)
    {
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos)
            throw arcade::Error("MainMenu - parseScore - Invalid score format.");

        std::string playerName = line.substr(0, colonPos);
        std::string scoreValueStr = line.substr(colonPos + 1);
        int scoreValue = 0;

        try {
            scoreValue = std::stoi(scoreValueStr);
        } catch (const std::invalid_argument &e) {
            throw arcade::Error("MainMenu - parseScore - Invalid score value format.");
        } catch (const std::out_of_range &e) {
            throw arcade::Error("MainMenu - parseScore - Score value out of range.");
        }
        return Score(playerName, scoreValue);
    }

    void MainMenu::stop()
    {
    }

    void MainMenu::handleMouseClick([[maybe_unused]] const Key &event, const std::pair<int, int> &clickPosition)
    {
        size_t startGameX = 14;
        size_t startGameY = 9;
        size_t endGameX = 24;
        size_t gameIndex = 0;
        std::unordered_map<std::pair<int, int>, size_t> gameCoordMap;

        size_t startGraphicX = 35;
        size_t startGraphicY = 9;
        size_t endGraphicX = 42;
        size_t graphicIndex = 0;
        std::unordered_map<std::pair<int, int>, size_t> graphicCoordMap;

        size_t currentStartY = 0;

        for ([[maybe_unused]] const auto &lib : _gameLibraries) {
            currentStartY = startGameY + gameIndex * 5;
            for (size_t y = currentStartY; y < currentStartY + 3; ++y)
                for (size_t x = startGameX; x < endGameX; ++x)
                    gameCoordMap[{x, y}] = gameIndex;
            ++gameIndex;
        }

        for ([[maybe_unused]] const auto &lib : _graphicLibraries) {
            currentStartY = startGraphicY + graphicIndex * 5;
            for (size_t y = currentStartY; y < currentStartY + 3; ++y)
                for (size_t x = startGraphicX; x < endGraphicX; ++x)
                    graphicCoordMap[{x, y}] = graphicIndex;
            ++graphicIndex;
        }

        if (gameCoordMap.contains(clickPosition)) {
            _selectedGameIndex = gameCoordMap[clickPosition];
            _isGameListChecked = true;
        }
        if (graphicCoordMap.contains(clickPosition)) {
            _selectedGraphicIndex = graphicCoordMap[clickPosition];
            _isGameListChecked = false;
        }
    }

    void MainMenu::applyEvents(IEvent *eventWrapper)
    {
        if (!eventWrapper)
            throw arcade::Error("MainMenu - applyEvents - Failed to apply events: Event wrapper is null.");

        TextMap tempTexts = _texts->getTextMap();

        if (tempTexts.size() != 0) {
            _currentGraphical = cleanLibName(tempTexts[{0, 0}].getStr());
            _texts->updateTextMap({{{0, 0}, Text(" ")}});
        }

        Key key = Key::KEY_LIST_END;

        while (1) {
            std::unique_ptr<IEventInfo> tempEventInfo = eventWrapper->getEvent();
            if (!tempEventInfo)
                break;
            key = tempEventInfo->getKey();
            if (key == Key::KEY_LIST_END || key == Key::NONE)
                break;
            if (key == Key::ENTER && _nameInput.length()) {
                selectLibraries(eventWrapper);
                break;
            }
            if (key == Key::MOUSE_BUTTON_LEFT || key == Key::MOUSE_BUTTON_RIGHT) {
                handleMouseClick(key, tempEventInfo->getMouseCoords());
                continue;
            }
            applyEvent(key);
        }
    }

    void MainMenu::selectLibraries(IEvent *eventWrapper)
    {
        if (_selectedGameIndex < _mainMenuIndex)
            for (std::size_t i = 0; i < _mainMenuIndex - _selectedGameIndex; ++i)
                eventWrapper->pushChangeEvent(ChangeKey::PREV_GAME_LIB);
        else
            for (std::size_t i = 0; i < _selectedGameIndex - _mainMenuIndex + 1; ++i)
                eventWrapper->pushChangeEvent(ChangeKey::NEXT_GAME_LIB);

        std::size_t currentLibIndex = 0;

        for (std::size_t i = 0; i < _graphicLibraries.size(); ++i)
            if (_graphicLibraries.at(i) == _currentGraphical)
                currentLibIndex = i;

        if (_selectedGraphicIndex < currentLibIndex)
            for (std::size_t i = 0; i < currentLibIndex - _selectedGraphicIndex; ++i)
                eventWrapper->pushChangeEvent(ChangeKey::PREV_GRAPHICAL_LIB);
        else if (_selectedGraphicIndex > currentLibIndex)
            for (std::size_t i = 0; i < _selectedGraphicIndex - currentLibIndex; ++i)
                eventWrapper->pushChangeEvent(ChangeKey::NEXT_GRAPHICAL_LIB);
    }

    void MainMenu::applyEvent(const Key &key)
    {
        switch (key) {
            case Key::UP_ARROW:
                moveUp();
                break;
            case Key::DOWN_ARROW:
                moveDown();
                break;
            case Key::LEFT_ARROW:
                switchList(true);
                break;
            case Key::RIGHT_ARROW:
                switchList(false);
                break;
            case Key::DELETE:
                deleteChar();
                break;
            default:
                if (isCharInput(key))
                    addChar(key);
                break;
        }
    }

    void MainMenu::moveUp()
    {
        if (_isGameListChecked) {
            if (_selectedGameIndex > 0)
                _selectedGameIndex--;
            else
                _selectedGameIndex = _gameLibraries.size() - 1;
        } else {
            if (_selectedGraphicIndex > 0)
                _selectedGraphicIndex--;
            else
                _selectedGraphicIndex = _graphicLibraries.size() - 1;
        }
    }

    void MainMenu::moveDown()
    {
        if (_isGameListChecked) {
            if (_selectedGameIndex < _gameLibraries.size() - 1)
                _selectedGameIndex++;
            else
                _selectedGameIndex = 0;
        } else {
            if (_selectedGraphicIndex < _graphicLibraries.size() - 1)
                _selectedGraphicIndex++;
            else
                _selectedGraphicIndex = 0;
        }
    }

    void MainMenu::switchList(bool left)
    {
        if (left)
            _isGameListChecked = true;
        else
            _isGameListChecked = false;
    }

    void MainMenu::addChar(Key key)
    {
        char inputChar = static_cast<char>(key) + ('A');
        _nameInput += inputChar;
    }

    void MainMenu::deleteChar()
    {
        if (!_nameInput.empty())
            _nameInput.pop_back();
    }

    bool MainMenu::isCharInput(Key key) const
    {
        return (key >= Key::A_KEY && key <= Key::Z_KEY);
    }

    void MainMenu::update([[maybe_unused]] float deltaTime)
    {
        clearScreen();
        drawBackground();
        drawUsernameText();
        drawGameList();
        drawGraphicList();
        drawScores();
    }

    void MainMenu::clearScreen()
    {
        _pixels->getPixelMap().clear();
        _texts->getTextMap().clear();
    }

    void MainMenu::drawBackground()
    {
        std::size_t winSizeX = 192;
        std::size_t winSizeY = 100;

        float winPercentage = 0.45f;
        float tempWinPercentage = 0.0f;

        std::size_t minX = static_cast<size_t>((static_cast<float>(winSizeX) * winPercentage));
        std::size_t minY = static_cast<size_t>((static_cast<float>(winSizeY) * winPercentage));

        std::size_t libCount = std::max(_gameLibraries.size(), _graphicLibraries.size());

        tempWinPercentage += static_cast<float>(libCount) * 0.05f;

        std::size_t sizeX = static_cast<size_t>((static_cast<float>(winSizeX) * tempWinPercentage));
        std::size_t sizeY = static_cast<size_t>((static_cast<float>(winSizeY) * tempWinPercentage));

        sizeX = std::max(minX, sizeX);
        sizeY = std::max(minY, sizeY);

        for (size_t x = 0; x < sizeX; ++x)
            for (size_t y = 0; y < sizeY; ++y)
                _pixels->getPixelMap()[{x, y}] = Pixel(50, 0, 127);
    }

    void MainMenu::drawUsernameText()
    {
        std::string userNameText = "USERNAME: \"" + _nameInput + "\"";
        _texts->getTextMap()[{5, 5}] = userNameText;

        drawTextBackground(5, 5, _texts->getTextMap()[{5, 5}].getStr().size(),
            Pixel(
                170,
                0,
                127,
                255,
                Pixel::PixelType::DEFAULT,
                '.'
            )
        );
    }

    void MainMenu::drawGameList()
    {
        size_t gameListStartY = 10;
        size_t gameListCenterX = 15;
        size_t highestGameTextSize = 0;

        for (size_t i = 0; i < _gameLibraries.size(); ++i) {
            std::string gameText = _gameLibraries[i];
            size_t yOffset = gameListStartY + i * 5;
            size_t xOffset = gameListCenterX;

            _texts->getTextMap()[{xOffset, yOffset}] = gameText;
            highestGameTextSize = std::max(highestGameTextSize, gameText.size());
        }

        for (size_t i = 0; i < _gameLibraries.size(); ++i) {
            std::string gameText = _gameLibraries[i];
            size_t yOffset = gameListStartY + i * 5;
            size_t xOffset = gameListCenterX;

            if (i == _selectedGameIndex) {
                if (_isGameListChecked) {
                    drawTextBackground(xOffset, yOffset, highestGameTextSize,
                        Pixel(
                            255,
                            255,
                            0,
                            255,
                            Pixel::PixelType::DEFAULT,
                            '.'
                        )
                    );
                } else {
                    drawTextBackground(xOffset, yOffset, highestGameTextSize,
                        Pixel(
                            255,
                            255,
                            255,
                            255,
                            Pixel::PixelType::DEFAULT,
                            '-'
                        )
                    );
                }
            } else {
                drawTextBackground(xOffset, yOffset, highestGameTextSize,
                    Pixel(
                        0,
                        255,
                        127,
                        255,
                        Pixel::PixelType::DEFAULT,
                        '_'
                    )
                );
            }
        }
    }

    void MainMenu::drawGraphicList()
    {
        size_t graphicListStartY = 10;
        size_t graphicListCenterX = 35;
        size_t highestGraphicTextSize = 0;

        for (size_t i = 0; i < _graphicLibraries.size(); ++i) {
            std::string graphicText = _graphicLibraries[i];
            size_t yOffset = graphicListStartY + i * 5;
            size_t xOffset = graphicListCenterX;

            _texts->getTextMap()[{xOffset, yOffset}] = graphicText;
            highestGraphicTextSize = std::max(highestGraphicTextSize, graphicText.size());
        }

        for (size_t i = 0; i < _graphicLibraries.size(); ++i) {
            std::string graphicText = _graphicLibraries[i];
            size_t yOffset = graphicListStartY + i * 5;
            size_t xOffset = graphicListCenterX;

            if (i == _selectedGraphicIndex) {
                if (!_isGameListChecked) {
                    drawTextBackground(xOffset, yOffset, highestGraphicTextSize,
                        Pixel(
                            255,
                            255,
                            0,
                            255,
                            Pixel::PixelType::DEFAULT,
                            '.'
                        )
                    );
                } else {
                    drawTextBackground(xOffset, yOffset, highestGraphicTextSize,
                        Pixel(
                            255,
                            255,
                            255,
                            255,
                            Pixel::PixelType::DEFAULT,
                            '-'
                        )
                    );
                }
            } else {
                drawTextBackground(xOffset, yOffset, highestGraphicTextSize,
                    Pixel(
                        0,
                        255,
                        127,
                        255,
                        Pixel::PixelType::DEFAULT,
                        '_'
                    )
                );
            }
        }
    }

    void MainMenu::drawTextBackground(size_t xOffset, size_t yOffset, size_t textLength, const Pixel &pixel)
    {
        for (float y = -1.0f; y < 2.0f; ++y)
            for (float x = -1.0f; x < static_cast<float>(textLength) / 1.5f + 1.0f; ++x)
                _pixels->getPixelMap()[{static_cast<int>(static_cast<float>(xOffset) + x), static_cast<int>(static_cast<float>(yOffset) + y)}] = pixel;
    }

    void MainMenu::sortScores(std::vector<Score> &scores)
    {
        std::sort(scores.begin(), scores.end(), [](Score one, Score two) {
            return one.getScoreValue() > two.getScoreValue();
        });
    }

    void MainMenu::drawScores()
    {
        std::vector<Score> &tempScores = _scores[_gameLibraries[_selectedGameIndex]];
        TextMap addedTexts = {};
        size_t index = 0;
        size_t x = 58;
        size_t y = 7;
        size_t highestScoreSize = 0;

        addedTexts[{x, y}] = Text("BEST SCORES:");
        x += 1;
        y += 3;

        sortScores(tempScores);

        for (const auto &score : tempScores) {
            if (score.getPlayerName().size() == 0)
                continue;
            if (++index == 10)
                break;
            addedTexts[{x, y}] = Text(score.getPlayerName() + ": " + std::to_string(score.getScoreValue()));
            highestScoreSize = std::max(highestScoreSize, addedTexts[{x, y}].getStr().size());
            y += 2;
        }
        _texts->updateTextMap(addedTexts);

        index = 0;
        x = 58;
        y = 7;

        drawTextBackground(x, y, addedTexts[{x, y}].getStr().size(),
            Pixel(
                170,
                0,
                127,
                255,
                Pixel::PixelType::DEFAULT,
                '.'
            )
        );

        x += 1;
        y += 3;
        for (const auto &score : tempScores) {
            if (score.getPlayerName().size() == 0)
                continue;
            if (++index == 10)
                break;
            drawTextBackground(x, y, highestScoreSize,
                Pixel(
                    170,
                    0,
                    127,
                    255,
                    Pixel::PixelType::DEFAULT,
                    '.'
                )
            );
            y += 2;
        }
    }

    void MainMenu::reload()
    {
    }

    int MainMenu::getScore()
    {
        return 0;
    }

    void MainMenu::draw(IGraphicalModule *graphicalModule)
    {
        graphicalModule->updatePixelsWrapper(_pixels.get());
        graphicalModule->updateTextsWrapper(_texts.get());
        graphicalModule->display();
    }

    std::string MainMenu::getName() const
    {
        return _nameInput;
    }

    std::string MainMenu::decryptData(const std::string &ciphertext, const std::string &key)
    {
        OpenSSL_add_all_algorithms();
        ERR_load_crypto_strings();

        const EVP_CIPHER *cipher = EVP_aes_256_cbc();
        const size_t ivLength = static_cast<size_t>(EVP_CIPHER_iv_length(cipher));

        std::string ivStr = ciphertext.substr(0, ivLength);
        std::vector<unsigned char> iv(ivStr.begin(), ivStr.end());
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
        EVP_DecryptInit_ex(ctx, cipher, nullptr, reinterpret_cast<const unsigned char *>(key.c_str()), iv.data());
        size_t plainTextLen = ciphertext.length() - ivLength + static_cast<size_t>(EVP_CIPHER_block_size(cipher));
        std::vector<unsigned char> plainText(plainTextLen);
        int len = 0;
        EVP_DecryptUpdate(ctx, plainText.data(), &len, reinterpret_cast<const unsigned char *>(ciphertext.c_str() + ivLength), static_cast<int>(ciphertext.length() - ivLength));
        plainTextLen = static_cast<size_t>(len);
        EVP_DecryptFinal_ex(ctx, plainText.data() + len, &len);
        plainTextLen += static_cast<size_t>(len);
        EVP_CIPHER_CTX_free(ctx);
        return std::string(reinterpret_cast<char*>(plainText.data()), plainTextLen);
    }
}
