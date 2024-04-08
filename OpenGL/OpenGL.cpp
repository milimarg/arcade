/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** uf TestGraphical
*/

#include "./OpenGL.hpp"

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

    Window::Window() : _windowHeight(0), _windowWidth(0), _isOpenFlag(false) {}
    Window::~Window() {}

    void test(void) {}

    void Window::openWindow(int width, int height)
    {
        _windowWidth = width;
        _windowHeight = height;
        _isOpenFlag = true;

        int argc = 1;
        const char *argv[1] = {"something"};
        glutInit(&argc, (char **)argv);
        glutDisplayFunc(test);

        int screen_width = glutGet(GLUT_SCREEN_WIDTH);
        int screen_height = glutGet(GLUT_SCREEN_HEIGHT);

        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(_windowWidth, _windowHeight);
        glutInitWindowPosition((screen_width / 2) - (_windowWidth / 2),
                               (screen_height / 2) - (_windowHeight / 2));
        id = glutCreateWindow("Window");
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(0, _windowWidth, _windowHeight, 0);
    }

    void Window::closeWindow()
    {
        _windowWidth = 0;
        _windowHeight = 0;
        _isOpenFlag = false;
        glutDestroyWindow(id);
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
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::displayPixels(IPixels *pixels)
    {
        int maxX = 0;
        int maxY = 0;
        for (const auto &pixel : pixels->getPixelMap()) {
            maxX = std::max(maxX, pixel.first.first);
            maxY = std::max(maxY, pixel.first.second);
        }
        int tempPixelSizeX = _windowWidth / (maxX + 1);
        int tempPixelSizeY = _windowHeight / (maxY + 1);
        int square_size = std::min(tempPixelSizeX, tempPixelSizeY);

        _currentPixelSizeX = square_size;
        _currentPixelSizeY = square_size;

        if (pixels) {
            for (const auto &pixel : pixels->getPixelMap()) {
                if (pixel.second.getType() == IPixel::PixelType::DEFAULT) {
                    displayDefaultPixel(pixel.first, pixel.second, _currentPixelSizeX, _currentPixelSizeY);
                }
                if (pixel.second.getType() == IPixel::PixelType::TEXTURED) {
                    displayDefaultPixel(pixel.first, pixel.second, _currentPixelSizeX, _currentPixelSizeY);
                    displayTexturedPixel(pixel.first, pixel.second);
                }
            }
        } else
            throw arcade::Error("OpenGL (Window) - displayPixels - Failed to display pixels: Pixels object is null.");
    }

    void Window::displayDefaultPixel(const std::pair<int, int> &coords, const arcade::Pixel &pixel,
        float currentPixelSize_X, float currentPixelSize_Y)
    {
        const int x = coords.first;
        const int y = coords.second;
        const float red = pixel.getRed() / 255.0f;
        const float green = pixel.getGreen() / 255.0f;
        const float blue = pixel.getBlue() / 255.0f;
        const float alpha = pixel.getAlpha() / 255.0f;
        glBegin(GL_QUADS);
        glColor4f(red, green, blue, alpha);
        glVertex2f(x * currentPixelSize_X,                      y * currentPixelSize_Y);
        glVertex2f(x * currentPixelSize_X + currentPixelSize_X, y * currentPixelSize_Y);
        glVertex2f(x * currentPixelSize_X + currentPixelSize_X, y * currentPixelSize_Y + currentPixelSize_Y);
        glVertex2f(x * currentPixelSize_X,                      y * currentPixelSize_Y + currentPixelSize_Y);
        glEnd();
    }

    void Window::displayTexturedPixel(const std::pair<int, int> &coords, const arcade::Pixel &pixel)
    {
        std::string textureName = pixel.getTexturePath();

        if (!std::filesystem::exists(textureName))
            return;

        std::pair<int, int> rectPosition = pixel.getRectPosition();
        std::pair<int, int> rectSize = pixel.getRectSize();
        int screenY = coords.second * rectSize.second;

        if (!_textureMap.contains(textureName)) {
            _textureMap[textureName] = Texture(textureName);
        }

        Texture &texture = _textureMap[textureName];
        if (texture.getBuffer() == nullptr)
            return;

        glBegin(GL_POINTS);
        for (int y = rectPosition.second; y < rectPosition.second + rectSize.second; y += 1) {
            int screenX = coords.first * rectSize.first;
            for (int x = rectPosition.first; x < rectPosition.first + rectSize.first; x += 1) {
                const unsigned char *p = texture.getBuffer() + ((y * texture.getWidth() + x) * 4);
                const Pixel pixel(*p, *(p + 1), *(p + 2), *(p + 3));
                float rescaledSizeX = (float)_currentPixelSizeX / (float)rectSize.first;
                float rescaledSizeY = (float)_currentPixelSizeY / (float)rectSize.second;
                displayDefaultPixel(std::make_pair(screenX, screenY), pixel, rescaledSizeX, rescaledSizeY);
                screenX += 1;
            }
            screenY += 1;
        }
        glEnd();
    }

    static void displayText(float x, float y, const Text &text)
    {
        const std::string &str = text.getStr();

        glColor4f(text.getRed() / 255.f, text.getGreen() / 255.f, text.getBlue() / 255.f, text.getAlpha() / 255.f);
        glRasterPos2f(x, y);
        for (size_t i = 0; i < str.size(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str.c_str()[i]);
        }
    }

    void Window::displayTexts(ITexts *texts)
    {
        TextMap textMap = texts->getTextMap();

        for (const auto &text : textMap) {
            int x = text.first.first * _currentPixelSizeX;
            int y = text.first.second * _currentPixelSizeY + _currentPixelSizeY;
            std::string str = text.second.getStr();

            displayText(x, y, text.second);
        }
    }

    void Window::display()
    {
    }

    OpenGL::OpenGL() :
        _pixels(nullptr),
        _event(nullptr),
        _window(nullptr),
        _keyTable({
            {27, Key::DELETE},
            {13, Key::ENTER},
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
            {'z', Key::Z_KEY},
            {8, Key::DELETE}
        }),
        _specialKeyTable({
            {GLUT_KEY_UP, Key::UP_ARROW},
            {GLUT_KEY_DOWN, Key::DOWN_ARROW},
            {GLUT_KEY_LEFT, Key::LEFT_ARROW},
            {GLUT_KEY_RIGHT, Key::RIGHT_ARROW},
        }),
        _changeKeyTable({
            {27, ChangeKey::ESCAPE}
        }),
        _specialChangeKeyTable({
            {GLUT_KEY_F1, ChangeKey::MAIN_MENU},
            {GLUT_KEY_F2, ChangeKey::PREV_GAME_LIB},
            {GLUT_KEY_F3, ChangeKey::NEXT_GAME_LIB},
            {GLUT_KEY_F4, ChangeKey::PREV_GRAPHICAL_LIB},
            {GLUT_KEY_F5, ChangeKey::NEXT_GRAPHICAL_LIB}
        })
    {
    }

    OpenGL::~OpenGL() {}

    void OpenGL::init()
    {
        createEventObject();
        createWindowObject();

        _window->openWindow(1920, 1080);
    }

    void OpenGL::stop()
    {
    }

    std::string OpenGL::getName() const
    {
        return "TestGraphical";
    }

    IEvent *OpenGL::getEventWrapper() const
    {
        return _event.get();
    }

    IWindow *OpenGL::getWindowWrapper() const
    {
        return _window.get();
    }

    void OpenGL::updatePixelsWrapper(IPixels *pixels)
    {
        _pixels = pixels;
    }

    void OpenGL::updateTextsWrapper(ITexts *texts)
    {
        _texts = texts;
    }

    void OpenGL::display() const
    {
        _window->clearScreen();
        _window->displayPixels(_pixels);
        _window->displayTexts(_texts);
        _window->display();

        glFlush();
    }

    void keyboardHandler(unsigned char key,
        int x __attribute_maybe_unused__, int y __attribute_maybe_unused__)
    {
        keysPressed[key] = true;
    }

    void specialKeyboardHandler(int key,
        int x __attribute_maybe_unused__, int y __attribute_maybe_unused__)
    {
        specialKeysPressed[key] = true;
    }

    void mouseHandler(int button, int state, int x, int y)
    {
        if (state != GLUT_DOWN)
            return;
        if (button == GLUT_LEFT_BUTTON) {
            mouseButtonPressed = ButtonPressed::LEFT;
            mouseX = x;
            mouseY = y;
            return;
        }
        if (button == GLUT_RIGHT_BUTTON) {
            mouseButtonPressed = ButtonPressed::RIGHT;
            mouseX = x;
            mouseY = y;
            return;
        }
        if (mouseButtonPressed != ButtonPressed::NONE)
            mouseButtonPressed = ButtonPressed::NONE;
    }

    void OpenGL::pollEvents()
    {
        glutMainLoopEvent();

        if (getWindowWrapper()->isOpen() && !glutGetWindow())
            getWindowWrapper()->closeWindow();

        glutKeyboardFunc(keyboardHandler);
        glutSpecialFunc(specialKeyboardHandler);

        for (auto it = keysPressed.begin(); it != keysPressed.end(); it += 1) {
            unsigned char index = it - keysPressed.begin();
            if (*it == true && _keyTable.contains(index)) {
                _event->pushEvent(_keyTable.at(index));
            }
        }
        for (auto it = specialKeysPressed.begin(); it != specialKeysPressed.end(); it += 1) {
            unsigned char index = it - specialKeysPressed.begin();
            if (*it == true && _specialKeyTable.contains(index)) {
                _event->pushEvent(_specialKeyTable.at(index));
            }
        }
        for (auto it = keysPressed.begin(); it != keysPressed.end(); it += 1) {
            unsigned char index = it - keysPressed.begin();
            if (*it == true && _changeKeyTable.contains(index)) {
                _event->pushChangeEvent(_changeKeyTable.at(index));
            }
        }
        for (auto it = specialKeysPressed.begin(); it != specialKeysPressed.end(); it += 1) {
            unsigned char index = it - specialKeysPressed.begin();
            if (*it == true && _specialChangeKeyTable.contains(index)) {
                _event->pushChangeEvent(_specialChangeKeyTable.at(index));
            }
        }

        glutMouseFunc(mouseHandler);

        if (mouseButtonPressed == ButtonPressed::LEFT) {
            _event->pushEvent(Key::MOUSE_BUTTON_LEFT, {mouseX / std::max(1, static_cast<Window*>(_window.get())->getCurrentPixelSizeX()), mouseY / std::max(1, static_cast<Window*>(_window.get())->getCurrentPixelSizeY())});
        } else if (mouseButtonPressed == ButtonPressed::RIGHT) {
            _event->pushEvent(Key::MOUSE_BUTTON_RIGHT, {mouseX / std::max(1, static_cast<Window*>(_window.get())->getCurrentPixelSizeX()), mouseY / std::max(1, static_cast<Window*>(_window.get())->getCurrentPixelSizeY())});
        }

        for (auto &key : keysPressed)
            key = false;
        for (auto &key : specialKeysPressed)
            key = false;
    }

    IEvent *OpenGL::createEventObject()
    {
        _event = std::make_unique<Event>();
        return _event.get();
    }

    IWindow *OpenGL::createWindowObject()
    {
        _window = std::make_unique<Window>();
        return _window.get();
    }
}
