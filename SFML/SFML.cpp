/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** SFML
*/

#include "./SFML.hpp"

namespace arcade
{
    Event::Event() {}
    Event::~Event() {}

    std::unique_ptr<IEventInfo> Event::getEvent()
    {
        if (_eventQueue.size() == 0)
            return std::make_unique<EventInfo>(Key::KEY_LIST_END);

        std::unique_ptr<IEventInfo> key = std::move(_eventQueue.front());
        _eventQueue.pop();

        return key;
    }

    std::unique_ptr<IEventInfo> Event::getChangeEvent()
    {
        if (_changeEventQueue.size() == 0)
            return std::make_unique<EventInfo>(ChangeKey::CHANGE_LIST_END);

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

    Window::Window() :
        _windowWidth(0),
        _windowHeight(0),
        _isOpenFlag(false),
        _window()
    {
    };

    Window::~Window()
    {
        _textureMap.clear();
    };

    void Window::openWindow(int width, int height)
    {
        _window.create(sf::VideoMode(width, height), "Window");

        _windowWidth = width;
        _windowHeight = height;
        _isOpenFlag = true;
    }

    void Window::closeWindow()
    {
        if (_window.isOpen()) {
            _window.close();
        }
        _windowWidth = 0;
        _windowHeight = 0;
        _isOpenFlag = false;
    }

    void Window::resizeWindow(int width, int height)
    {
        _windowWidth = width;
        _windowHeight = height;
    }

    bool Window::isOpen() const
    {
        return _isOpenFlag;
    }

    void Window::clearScreen()
    {
        _window.clear();
        _vertexArray.clear();
    }

    void Window::displayPixels(IPixels *pixels)
    {
        if (!pixels)
            throw arcade::Error("SFML (Window) - displayPixels - Failed to display pixels: Pixels object is null.");

        PixelsMap pixelMap = pixels->getPixelMap();

        int maxX = 0;
        int maxY = 0;

        for (const auto &pixel : pixelMap) {
            maxX = std::max(maxX, pixel.first.first);
            maxY = std::max(maxY, pixel.first.second);
        }

        int tempPixelSizeX = _windowWidth / (maxX + 1);
        int tempPixelSizeY = _windowHeight / (maxY + 1);

        int pixelSizeX = std::min(tempPixelSizeX, tempPixelSizeY);
        int pixelSizeY = pixelSizeX;

        _currentPixelSizeX = pixelSizeX;
        _currentPixelSizeY = pixelSizeY;

        for (const auto &pixel : pixelMap) {
            switch (pixel.second.getType()) {
                case Pixel::PixelType::DEFAULT:
                    displayDefaultPixel(pixel.first, pixel.second);
                    break;
                case Pixel::PixelType::TEXTURED:
                    displayTexturedPixel(pixel.first, pixel.second);
                    break;
                default:
                    std::cerr << "Pixel type not recognized" << std::endl;
                    break;
            }
        }
        _window.draw(_vertexArray);
    }

    void Window::displayDefaultPixel(const std::pair<int, int> &coords, const arcade::Pixel &pixel)
    {
        int x = coords.first * _currentPixelSizeX;
        int y = coords.second * _currentPixelSizeY;

        _vertexArray.setPrimitiveType(sf::PrimitiveType::Quads);

        sf::Color color(pixel.getRed(), pixel.getGreen(), pixel.getBlue(), pixel.getAlpha());

        _vertexArray.append(sf::Vertex(sf::Vector2f(x, y), color));
        _vertexArray.append(sf::Vertex(sf::Vector2f(x + _currentPixelSizeX, y), color));
        _vertexArray.append(sf::Vertex(sf::Vector2f(x + _currentPixelSizeX, y + _currentPixelSizeY), color));
        _vertexArray.append(sf::Vertex(sf::Vector2f(x, y + _currentPixelSizeY), color));
    }

    void Window::displayTexturedPixel(const std::pair<int, int> &coords, const arcade::Pixel &pixel)
    {
        int x = coords.first * _currentPixelSizeX;
        int y = coords.second * _currentPixelSizeY;
        std::string textureName = pixel.getTexturePath();

        if (!std::filesystem::exists(textureName)) {
            displayDefaultPixel(coords, pixel);
            return;
        }

        if (!_textureMap.contains(textureName)) {
            sf::Texture texture;

            if (!texture.loadFromFile(textureName)) {
                displayDefaultPixel(coords, pixel);
                return;
            }

            _textureMap[textureName] = texture;
        }

        std::pair<int, int> rectPosition = pixel.getRectPosition();
        std::pair<int, int> rectSize = pixel.getRectSize();

        sf::Sprite sprite;

        sprite.setTexture(_textureMap[textureName]);
        sprite.setTextureRect(sf::IntRect(rectPosition.first, rectPosition.second,
                                          rectSize.first, rectSize.second));
        sprite.setPosition(x, y);
        sprite.setScale(_currentPixelSizeX / (float)rectSize.first,
                        _currentPixelSizeY / (float)rectSize.second);
        _window.draw(sprite);
    }

    void Window::displayTexts(ITexts *texts)
    {
        if (!texts)
            throw arcade::Error("SFML (Window) - displayTexts - Failed to display texts: Texts object is null.");

        TextMap textMap = texts->getTextMap();

        int fontSize = _currentPixelSizeX;

        static const std::string fontName = "Fonts/arial.ttf";

        if (!_currentFont.loadFromFile(fontName))
            throw arcade::Error("SFML (Window) - displayTexts - Failed to load font:" + fontName);
        if (!_fontLoaded)
            _fontLoaded = true;

        for (const auto &text : textMap) {
            int x = text.first.first * _currentPixelSizeX;
            int y = text.first.second * _currentPixelSizeY;
            std::string str = text.second.getStr();
            if (str.size() == 0)
                continue;
            sf::Text textObj(str, _currentFont, fontSize);
            sf::Color textColor(text.second.getRed(), text.second.getGreen(),
                                text.second.getBlue(), text.second.getAlpha());
            textObj.setPosition(x, y);
            textObj.setFillColor(textColor);
            textObj.setOutlineColor(textColor);
            _window.draw(textObj);
        }
    }

    void Window::display()
    {
        _window.display();
    }

    sf::RenderWindow &Window::getRenderWindow()
    {
        return _window;
    }

    SFML::SFML() :
        _pixels(nullptr),
        _texts(nullptr),
        _event(nullptr),
        _window(nullptr),
        _keyTable({
            {sf::Keyboard::Key::Up, Key::UP_ARROW},
            {sf::Keyboard::Key::Down, Key::DOWN_ARROW},
            {sf::Keyboard::Key::Left, Key::LEFT_ARROW},
            {sf::Keyboard::Key::Right, Key::RIGHT_ARROW},
            {sf::Keyboard::Key::BackSpace, Key::DELETE},
            {sf::Keyboard::Key::Return, Key::ENTER},
            {sf::Keyboard::Key::A, Key::A_KEY},
            {sf::Keyboard::Key::B, Key::B_KEY},
            {sf::Keyboard::Key::C, Key::C_KEY},
            {sf::Keyboard::Key::D, Key::D_KEY},
            {sf::Keyboard::Key::E, Key::E_KEY},
            {sf::Keyboard::Key::F, Key::F_KEY},
            {sf::Keyboard::Key::G, Key::G_KEY},
            {sf::Keyboard::Key::H, Key::H_KEY},
            {sf::Keyboard::Key::I, Key::I_KEY},
            {sf::Keyboard::Key::J, Key::J_KEY},
            {sf::Keyboard::Key::K, Key::K_KEY},
            {sf::Keyboard::Key::L, Key::L_KEY},
            {sf::Keyboard::Key::M, Key::M_KEY},
            {sf::Keyboard::Key::N, Key::N_KEY},
            {sf::Keyboard::Key::O, Key::O_KEY},
            {sf::Keyboard::Key::P, Key::P_KEY},
            {sf::Keyboard::Key::Q, Key::Q_KEY},
            {sf::Keyboard::Key::R, Key::R_KEY},
            {sf::Keyboard::Key::S, Key::S_KEY},
            {sf::Keyboard::Key::T, Key::T_KEY},
            {sf::Keyboard::Key::U, Key::U_KEY},
            {sf::Keyboard::Key::V, Key::V_KEY},
            {sf::Keyboard::Key::W, Key::W_KEY},
            {sf::Keyboard::Key::X, Key::X_KEY},
            {sf::Keyboard::Key::Y, Key::Y_KEY},
            {sf::Keyboard::Key::Z, Key::Z_KEY}
        }),
        _changeKeyTable({
            {sf::Keyboard::Key::F1, ChangeKey::MAIN_MENU},
            {sf::Keyboard::Key::F2, ChangeKey::PREV_GAME_LIB},
            {sf::Keyboard::Key::F3, ChangeKey::NEXT_GAME_LIB},
            {sf::Keyboard::Key::F4, ChangeKey::PREV_GRAPHICAL_LIB},
            {sf::Keyboard::Key::F5, ChangeKey::NEXT_GRAPHICAL_LIB},
            {sf::Keyboard::Key::Escape, ChangeKey::ESCAPE}
        })
    {
    }

    SFML::~SFML() {}

    void SFML::init()
    {
        createEventObject();
        createWindowObject();

        _window->openWindow(1920, 1000);
    }

    void SFML::stop()
    {
        _window->closeWindow();
    }

    std::string SFML::getName() const
    {
        return "SFML";
    }

    IEvent *SFML::getEventWrapper() const
    {
        return _event.get();
    }

    IWindow *SFML::getWindowWrapper() const
    {
        return _window.get();
    }

    void SFML::updatePixelsWrapper(IPixels *pixels)
    {
        _pixels = pixels;
    }

    void SFML::updateTextsWrapper(ITexts *texts)
    {
        _texts = texts;
    }

    void SFML::pollEvents()
    {
        sf::Event event;

        while ((((Window *)(_window.get()))->getRenderWindow()).pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window->closeWindow();
            } else if (event.type == sf::Event::KeyPressed) {
                for (auto &key : _keyTable)
                    if (sf::Keyboard::isKeyPressed(key.first))
                        _event->pushEvent(key.second);
                for (auto &key : _changeKeyTable)
                    if (sf::Keyboard::isKeyPressed(key.first))
                        _event->pushChangeEvent(key.second);
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    _event->pushEvent(Key::MOUSE_BUTTON_LEFT, {event.mouseButton.x / std::max(1, static_cast<Window*>(_window.get())->getCurrentPixelSizeX()), event.mouseButton.y / std::max(1, static_cast<Window*>(_window.get())->getCurrentPixelSizeY())});
                } else if (event.mouseButton.button == sf::Mouse::Button::Right) {
                    _event->pushEvent(Key::MOUSE_BUTTON_RIGHT, {event.mouseButton.x / std::max(1, static_cast<Window*>(_window.get())->getCurrentPixelSizeX()), event.mouseButton.y / std::max(1, static_cast<Window*>(_window.get())->getCurrentPixelSizeY())});
                }
            }
        }
    }

    void SFML::display() const
    {
        _window->clearScreen();
        _window->displayPixels(_pixels);
        _window->displayTexts(_texts);
        _window->display();
    }

    IEvent *SFML::createEventObject()
    {
        _event = std::make_unique<Event>();
        return _event.get();
    }

    IWindow *SFML::createWindowObject()
    {
        _window = std::make_unique<Window>();
        return _window.get();
    }
}
