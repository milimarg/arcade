/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** NCurses
*/

#include "./NCurses.hpp"

namespace arcade
{
    Event::Event() {}
    Event::~Event() {}

    std::unique_ptr<IEventInfo> Event::getEvent()
    {
        if (_eventQueue.size() == 0)
            return std::move(std::make_unique<EventInfo>(Key::KEY_LIST_END));

        std::unique_ptr<IEventInfo> key = std::move(_eventQueue.front());
        _eventQueue.pop();

        return key;
    }

    std::unique_ptr<IEventInfo> Event::getChangeEvent()
    {
        if (_changeEventQueue.size() == 0)
            return std::move(std::make_unique<EventInfo>(ChangeKey::CHANGE_LIST_END));

        std::unique_ptr<IEventInfo> key = std::move(_changeEventQueue.front());
        _changeEventQueue.pop();

        return key;
    }

    void Event::pushEvent(const Key &key)
    {
        _eventQueue.push(std::make_unique<EventInfo>(key));
    }

    void Event::pushEvent(const Key &key, std::pair<int, int> mouseCoords)
    {
        _eventQueue.push(std::make_unique<EventInfo>(key, mouseCoords));
    }

    void Event::pushChangeEvent(const ChangeKey &changeKey)
    {
        _changeEventQueue.push(std::make_unique<EventInfo>(changeKey));
    }

    void Event::clearEventQueue()
    {
        while (!_eventQueue.empty())
            _eventQueue.pop();
    }

    void Event::clearChangeEventQueue()
    {
        while (!_changeEventQueue.empty())
            _changeEventQueue.pop();
    }

    const std::vector<Pixel> pixelColor = {
        Pixel(0, 0, 0), // BLACK
        Pixel(255, 0, 0), // RED
        Pixel(0, 255, 0), // GREEN
        Pixel(255, 255, 0), // YELLOW
        Pixel(0, 0, 255), // BLUE
        Pixel(255, 0, 255), // MAGENTA
        Pixel(0, 255, 255), // CYAN
        Pixel(255, 255, 255), // WHITE
    };

    Window::Window() :
        _windowHeightMin(0),
        _windowWidthMin(0),
        _window(nullptr),
        _isOpenFlag(false),
        _intensityLevels(4),
        _colorVariations(_intensityLevels * _intensityLevels * _intensityLevels),
        _font({})
    {
        loadFont("./Fonts/NCurses/GeneratedFont/");
    };

    Window::~Window()
    {
        closeWindow();
    };

    void Window::loadFont(const std::string &directoryPath)
    {
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                std::string filePath = entry.path().string();
                std::string fileName = entry.path().filename().string();

                size_t startPos = fileName.find_first_of('[');
                size_t endPos = fileName.find_last_of(']');

                if (startPos == std::string::npos || endPos == std::string::npos)
                    continue;

                std::string character = fileName.substr(startPos + 1, endPos - startPos - 1);
                if (character == "slash")
                    character = "/";

                std::ifstream file(filePath);
                if (file.is_open()) {
                    std::stringstream buffer;
                    buffer << file.rdbuf();
                    std::string content = buffer.str();
                    file.close();

                    _font[character] = content;
                } else {
                    std::cerr << "Failed to open font file: " << filePath << std::endl;
                }
            }
        }
    }

    const std::vector<int> ncursesColor = {
        COLOR_BLACK,
        COLOR_RED,
        COLOR_GREEN,
        COLOR_YELLOW,
        COLOR_BLUE,
        COLOR_MAGENTA,
        COLOR_CYAN,
        COLOR_WHITE
    };

    void Window::initColor()
    {
        // for (size_t i = 0; i < ncursesColor.size(); ++i)
        //     init_pair(i, ncursesColor[i], COLOR_BLACK);

        int colorScale = 1000;

        for (int r = 0; r < _intensityLevels; ++r) {
            for (int g = 0; g < _intensityLevels; ++g) {
                for (int b = 0; b < _intensityLevels; ++b) {
                    int pairIndex = r * _intensityLevels * _intensityLevels + g * _intensityLevels + b + 1;

                    init_color(pairIndex, r * colorScale / (_intensityLevels - 1), g * colorScale / (_intensityLevels - 1), b * colorScale / (_intensityLevels - 1));
                    init_pair(pairIndex, pairIndex, pairIndex);
                }
            }
        }
    }

    void Window::openWindow(int width, int height)
    {
        _windowWidthMin = width;
        _windowHeightMin = height;
        _window = initscr();
        _isOpenFlag = true;

        curs_set(0);
        start_color();
        initColor();
        cbreak();
        noecho();
        mousemask(BUTTON1_PRESSED, NULL);
        keypad(_window, TRUE);
    }

    void Window::closeWindow()
    {
        endwin();
        _windowWidthMin = 0;
        _windowHeightMin = 0;
        _window = nullptr;
        _isOpenFlag = false;
    }

    void Window::resizeWindow([[maybe_unused]] int width, [[maybe_unused]] int height)
    {
    }

    bool Window::isOpen() const
    {
        return _isOpenFlag && _window != nullptr;
    }

    void Window::clearScreen()
    {
        if (_window == nullptr)
            throw arcade::Error("Ncurses (Window) - clearScreen - Failed to clear: Window is null.");
        refresh();
        if (_canClear)
            clear();
    }

    double Window::getDistanceColor(int r, int g, int b, Pixel pixel)
    {
        int red = pixel.getRed();
        int green = pixel.getGreen();
        int blue = pixel.getBlue();

        int dr = r - red;
        int dg = g - green;
        int db = b - blue;
        double distance = std::sqrt(dr * dr + dg * dg + db * db);

        return distance;
    }

    std::pair<int, int> Window::getWindowCoord(int x, int y)
    {
        int trueX = x;
        int trueY = y;

        switch (_viewMode) {
            case ViewMode::STANDARD:
                trueX /= 2;
                break;
            case ViewMode::DITHERING:
                trueX /= 2;
                trueX /= std::max(1, _ditheringTextureSize);
                trueY /= std::max(1, _ditheringTextureSize);
                break;
            default:
                break;
        }

        return std::make_pair(trueX, trueY);
    }

    void Window::toggleEnhancedDithering()
    {
        _enhancedDithering = !_enhancedDithering;
        if (_enhancedDithering) {
            loadFont("./Fonts/NCurses/GeneratedBigFont/");
        } else {
            loadFont("./Fonts/NCurses/GeneratedFont/");
        }
    }

    int Window::getShadedColorPair(int r, int g, int b)
    {
        int rLevel = r * (_intensityLevels - 1) / 255;
        int gLevel = g * (_intensityLevels - 1) / 255;
        int bLevel = b * (_intensityLevels - 1) / 255;
        return rLevel * _intensityLevels * _intensityLevels + gLevel * _intensityLevels + bLevel + 1;
    }

    int Window::getPairColor(int r, int g, int b)
    {
        int closeColor = 0;
        int distanceColor = getDistanceColor(r, g, b, pixelColor[0]);

        for (size_t i = 1; i < pixelColor.size(); ++i) {
            Pixel currentPixel = pixelColor[i];
            int newDistance = getDistanceColor(r, g, b, currentPixel);
            if (newDistance < distanceColor) {
                distanceColor = newDistance;
                closeColor = i;
            }
        }
        return closeColor;
    }

    void Window::displayPixels(IPixels *pixels)
    {
        int middleWidth = (COLS / 2);
        int middleHeight = (LINES / 2);

        if (_window == nullptr)
            throw arcade::Error("Ncurses (Window) - displayPixels - Failed to display pixels: Window is null.");
        if (!pixels)
            throw arcade::Error("Ncurses (Window) - displayPixels - Failed to display pixels: Pixels object is null.");

        if (LINES < _windowHeightMin || COLS < _windowWidthMin) {
            mvprintw(middleHeight, middleWidth - 10, "Resize the window !");
            return;
        }
        PixelsMap pixelMap = pixels->getPixelMap();

        _currentDitheringTextureSize = _viewMode == ViewMode::STANDARD ? 1 : _ditheringTextureSize;
        if (_viewMode == ViewMode::DITHERING && _enhancedDithering)
            _currentDitheringTextureSize *= 2;

        for (const auto &pixel : pixelMap) {
            switch (pixel.second.getType()) {
                case Pixel::PixelType::TEXTURED:
                    if (_viewMode == ViewMode::DITHERING) {
                        displayTexturedPixel(pixel.first, pixel.second);
                        break;
                    } else {
                        displayDefaultPixel(pixel.first,
                                            pixel.second,
                                            _currentDitheringTextureSize,
                                            _currentDitheringTextureSize);
                        break;
                    }
                case Pixel::PixelType::DEFAULT:
                    displayDefaultPixel(pixel.first,
                                        pixel.second,
                                        _currentDitheringTextureSize,
                                        _currentDitheringTextureSize);
                    break;
                default:
                    std::cerr << "Pixel type not recognized" << std::endl;
                    break;
            }
        }
    }

    void Window::displayDefaultPixel(const std::pair<int, int> &coords, const arcade::Pixel &pixel,
                                     int shiftX, int shiftY)
    {
        int x = coords.first * shiftX;
        int y = coords.second * shiftY;
        int pair = getShadedColorPair(pixel.getRed(), pixel.getGreen(), pixel.getBlue());

        if (!_enhancedDithering || _viewMode != ViewMode::DITHERING) {
            x *= 2;

            attron(COLOR_PAIR(pair));
            for (int tempY = 0; tempY < shiftY; tempY += 1) {
                for (int tempX = 0; tempX < shiftX * 2; tempX += 2) {
                    mvaddch(y + tempY, x + tempX, pixel.getChar());
                    mvaddch(y + tempY, x + 1 + tempX, pixel.getChar());
                }
            }
            attroff(COLOR_PAIR(pair));
        } else {
            x *= 4;

            attron(COLOR_PAIR(pair));
            for (int tempY = 0; tempY < shiftY; tempY += 1) {
                for (int tempX = 0; tempX < shiftX * 4; tempX += 2) {
                    mvaddch(y + tempY, x + tempX, pixel.getChar());
                    mvaddch(y + tempY, x + 1 + tempX, pixel.getChar());

                    mvaddch(y + tempY, x + tempX + 1, pixel.getChar());
                    mvaddch(y + tempY, x + 1 + tempX + 1, pixel.getChar());
                }
            }
            attroff(COLOR_PAIR(pair));
        }
    }

    void Window::displayTexturedPixel(const std::pair<int, int> &coords, const arcade::Pixel &pixel)
    {
        std::string textureName = pixel.getTexturePath();

        if (!std::filesystem::exists(textureName)) {
            displayDefaultPixel(coords, pixel, _ditheringTextureSize, _ditheringTextureSize);
            return;
        }

        std::pair<int, int> rectPosition = pixel.getRectPosition();
        std::pair<int, int> rectSize = pixel.getRectSize();
        int screenY = coords.second * 4;
        if (_enhancedDithering)
            screenY *= 2;

        if (!_textureMap.contains(textureName)) {
            Texture texture(textureName);
            if (!texture.getBuffer()) {
                displayDefaultPixel(coords, pixel, _ditheringTextureSize, _ditheringTextureSize);
                return;
            }
            _textureMap[textureName] = texture;
        }

        Texture &texture = _textureMap[textureName];
        if (texture.getBuffer() == nullptr)
            return;

        int chunkSizeX = std::max(1.0f, (float)rectSize.first / 8);
        int chunkSizeY = std::max(1.0f, (float)rectSize.second / 8);

        for (int y = rectPosition.second; y < rectPosition.second + rectSize.second; y += 1) {
            if (y >= texture.getHeight())
                break;
            int screenX = coords.first * 4;
            if (_enhancedDithering)
                screenX *= 2;

            if (_enhancedDithering || (int)(y / chunkSizeY) % 2 == 0) {
                for (int x = rectPosition.first; x < rectPosition.first + rectSize.first; x += 1) {
                    if (x >= texture.getWidth())
                        continue;
                    if (_enhancedDithering || (int)(x / chunkSizeX) % 2 == 0) {
                        // '% 2' to get half values
                        const unsigned char *p = texture.getBuffer() + ((y * texture.getWidth() + x) * 4);
                        Pixel customPixel(*p, *(p + 1), *(p + 2), *(p + 3));
                        customPixel.setChar('#');
                        customPixel.setType(arcade::Pixel::PixelType::TEXTURED);
                        displayDefaultPixel(std::make_pair(screenX, screenY), customPixel, 1, 1);
                        screenX += 1;
                    }
                }
                screenY += 1;
            }
        }
    }

    void Window::displayChar(char c, int &currentX, int &currentY, int &x, int &y)
    {
        std::string character(1, c);
        if (_font.contains(character)) {
            std::string charContent = _font[character];
            std::istringstream iss(charContent);
            std::string line;

            size_t nextLinePos = charContent.find('\n');
            if (nextLinePos == std::string::npos) {
                mvprintw(y, x, "%s", charContent.c_str());
                currentX += charContent.length();
            } else {
                int savedX = currentX;
                while (std::getline(iss, line, '\n')) {
                    mvprintw(y, x, "%s", line.c_str());
                    ++y;
                    currentX = std::max(currentX, x + (int)line.length());
                    x = savedX;
                }
            }
        } else {
            mvprintw(y, x, "%c", c);
            ++currentX;
        }
    }

    void Window::displayTexts(ITexts *texts)
    {
        if (_window == nullptr)
            throw arcade::Error("Ncurses (Window) - displayTexts - Failed to display texts: Window is null.");
        if (!texts)
            throw arcade::Error("Ncurses (Window) - displayTexts - Failed to display texts: Texts object is null.");

        if (LINES < _windowHeightMin || COLS < _windowWidthMin)
            return;

        TextMap textMap = texts->getTextMap();

        int backgroundPair = 42;
        attron(A_BOLD);

        if (_viewMode == ViewMode::STANDARD) {
            for (const auto &text : textMap) {
                int x = text.first.first * _currentDitheringTextureSize * 2;
                int y = text.first.second * _currentDitheringTextureSize;

                std::string str = text.second.getStr();
                mvprintw(y, x, "%s", text.second.getStr().data());
            }
            attroff(A_BOLD);
            return;
        }

        for (const auto &text : textMap) {
            int x = text.first.first * (_currentDitheringTextureSize * 2);
            int y = text.first.second * _currentDitheringTextureSize;

            if (_enhancedDithering)
                x *= 2;

            std::string str = text.second.getStr();

            int currentX = x;
            int currentY = y;

            for (char c : str) {
                y = currentY;
                x = currentX;

                if (c == '\n') {
                    currentY += 10; // ? average char height
                    currentX = text.first.first * (_currentDitheringTextureSize * 2);
                    if (_enhancedDithering)
                        currentX *= 2;
                    continue;
                }

                displayChar(c, currentX, currentY, x, y);

                y = currentY;
                x = currentX;
                displayChar(' ', currentX, currentY, x, y);
            }
        }
        attroff(A_BOLD);
    }

    void Window::display()
    {
        if (_window == nullptr)
            throw arcade::Error("Ncurses (Window) - display - Failed to display: Window is null.");
    }

    NCurses::NCurses() :
        _pixels(nullptr),
        _texts(nullptr),
        _event(nullptr),
        _window(nullptr),
        _keyTable({
            {KEY_UP, Key::UP_ARROW},
            {KEY_DOWN, Key::DOWN_ARROW},
            {KEY_LEFT, Key::LEFT_ARROW},
            {KEY_RIGHT, Key::RIGHT_ARROW},
            {KEY_BACKSPACE, Key::DELETE},
            {'\n', Key::ENTER},
            {'a', Key::A_KEY},
            {'b', Key::B_KEY},
            {'c', Key::C_KEY},
            {'d', Key::D_KEY},
            {'e', Key::E_KEY},
            {'f', Key::F_KEY},
            {'g', Key::G_KEY},
            {'h', Key::H_KEY},
            {'i', Key::I_KEY},
            {'j', Key::J_KEY},
            {'k', Key::K_KEY},
            {'l', Key::L_KEY},
            {'m', Key::M_KEY},
            {'n', Key::N_KEY},
            {'o', Key::O_KEY},
            {'p', Key::P_KEY},
            {'q', Key::Q_KEY},
            {'r', Key::R_KEY},
            {'s', Key::S_KEY},
            {'t', Key::T_KEY},
            {'u', Key::U_KEY},
            {'v', Key::V_KEY},
            {'w', Key::W_KEY},
            {'x', Key::X_KEY},
            {'y', Key::Y_KEY},
            {'z', Key::Z_KEY}
        }),
        _changeKeyTable({
            {KEY_F(1), ChangeKey::MAIN_MENU},
            {KEY_F(2), ChangeKey::PREV_GAME_LIB},
            {KEY_F(3), ChangeKey::NEXT_GAME_LIB},
            {KEY_F(4), ChangeKey::PREV_GRAPHICAL_LIB},
            {KEY_F(5), ChangeKey::NEXT_GRAPHICAL_LIB},
            {27, ChangeKey::ESCAPE},
        })
    {
    }

    NCurses::~NCurses() {}

    void NCurses::init()
    {
        createEventObject();
        createWindowObject();
        _window->openWindow(80, 40);
    }

    void NCurses::stop()
    {
        if (_window)
            _window->closeWindow();
    }

    std::string NCurses::getName() const
    {
        return "NCurses";
    }

    IEvent *NCurses::getEventWrapper() const
    {
        return _event.get();
    }

    IWindow *NCurses::getWindowWrapper() const
    {
        return _window.get();
    }

    void NCurses::updatePixelsWrapper(IPixels *pixels)
    {
        _pixels = pixels;
    }

    void NCurses::updateTextsWrapper(ITexts *texts)
    {
        _texts = texts;
    }

    void NCurses::pollEvents()
    {
        timeout(0);
        int ch;
        MEVENT event;

        while ((ch = getch()) != 0 && ch != ERR) {
            if (_keyTable.contains(ch))
                _event->pushEvent(_keyTable.at(ch));
            if (ch == KEY_MOUSE)
                if(getmouse(&event) == OK) {
                    std::pair<int, int> coords = ((Window *)_window.get())->getWindowCoord(event.x, event.y);
                    _event->pushEvent(Key::MOUSE_BUTTON_LEFT, coords);
                }
            if (_changeKeyTable.contains(ch))
                _event->pushChangeEvent(_changeKeyTable.at(ch));
            if (ch == KEY_F(6)) {
                Window *tempWindow = (Window *)(_window.get());
                if (tempWindow->getViewMode() == Window::ViewMode::STANDARD)
                    tempWindow->setViewMode(Window::ViewMode::DITHERING);
                else
                    tempWindow->setViewMode(Window::ViewMode::STANDARD);
            }
            if (ch == KEY_F(7)) {
                Window *tempWindow = (Window *)(_window.get());
                tempWindow->setCanClear(!tempWindow->getCanClear());
            }
            if (ch == KEY_F(8)) {
                Window *tempWindow = (Window *)(_window.get());
                tempWindow->toggleEnhancedDithering();
            }
        }
    }

    void NCurses::display() const
    {
        if (!_window->isOpen())
            throw arcade::Error("Ncurses - display - Failed to display pixels: Window is close.");

        _window->clearScreen();
        _window->displayPixels(_pixels);
        _window->displayTexts(_texts);
        _window->display();
    }

    IEvent *NCurses::createEventObject()
    {
        _event = std::make_unique<Event>();
        return _event.get();
    }

    IWindow *NCurses::createWindowObject()
    {
        _window = std::make_unique<Window>();
        return _window.get();
    }
}
