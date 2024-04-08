/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Sdl2
*/

#include "./Sdl2.hpp"

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
        _window(nullptr),
        _renderer(nullptr),
        _font(nullptr)
    {
    };

    Window::~Window()
    {
        for (const auto &texture : _textureMap)
            SDL_DestroyTexture(texture.second);
    };

    void Window::openWindow(int width, int height)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            throw arcade::Error("SDL (Window) - openWindow - SDL could not initialize. SDL_Error: " + std::string(SDL_GetError()));

        _window = SDL_CreateWindow(
            "Arcade",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_SHOWN
        );

        if (_window == nullptr)
            throw arcade::Error("SDL (Window) - openWindow - Window could not be created. SDL_Error: " + std::string(SDL_GetError()));

        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
        if (_renderer == nullptr)
            throw arcade::Error("SDL (Window) - openWindow - Renderer could not be created. SDL_Error: " + std::string(SDL_GetError()));

        _windowWidth = width;
        _windowHeight = height;
        _isOpenFlag = true;
    }

    void Window::closeWindow()
    {
        if (_window != nullptr) {
            SDL_DestroyRenderer(_renderer);
            SDL_DestroyWindow(_window);
            _window = nullptr;
            _renderer = nullptr;
        }

        _windowWidth = 0;
        _windowHeight = 0;
        _isOpenFlag = false;
        SDL_Quit();
    }

    void Window::resizeWindow(int width, int height)
    {
        if (_window != nullptr) {
            SDL_SetWindowSize(_window, width, height);
        }

        _windowWidth = width;
        _windowHeight = height;
    }

    bool Window::isOpen() const
    {
        return _isOpenFlag && _window != nullptr;
    }

    void Window::clearScreen()
    {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);
    }

    void Window::displayPixels(IPixels *pixels)
    {
        if (_renderer == nullptr)
            throw arcade::Error("SDL (Window) - displayPixels - Failed to display pixels: Renderer is null.");

        if (!pixels)
            throw arcade::Error("SDL (Window) - displayPixels - Failed to display pixels: Pixels object is null.");

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
                    displayDefaultPixel(pixel.first, pixel.second);
                    displayTexturedPixel(pixel.first, pixel.second);
                    break;
                default:
                    std::cout << "Pixel type not recognized" << std::endl;
                    break;
            }
        }
    }

    void Window::displayDefaultPixel(const std::pair<int, int> &coords, const arcade::Pixel &pixel)
    {
        int x = coords.first * _currentPixelSizeX;
        int y = coords.second * _currentPixelSizeY;

        SDL_SetRenderDrawColor(_renderer, pixel.getRed(), pixel.getGreen(), pixel.getBlue(), 255);

        SDL_Rect rect = { x, y, _currentPixelSizeX, _currentPixelSizeY };
        SDL_RenderFillRect(_renderer, &rect);
    }

    void Window::displayTexturedPixel(const std::pair<int, int> &coords, const arcade::Pixel &pixel)
    {
        int x = coords.first * _currentPixelSizeX;
        int y = coords.second * _currentPixelSizeY;
        std::string textureName = pixel.getTexturePath();

        if (!std::filesystem::exists(textureName))
            return;

        if (!_textureMap.contains(textureName)) {
            SDL_Surface *textureSurface = IMG_Load(textureName.c_str());

            if (!textureSurface)
                return;

            SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, textureSurface);

            if (!texture)
                return;

            SDL_FreeSurface(textureSurface);

            _textureMap[textureName] = texture;
        }

        std::pair<int, int> rectPosition = pixel.getRectPosition();
        std::pair<int, int> rectSize = pixel.getRectSize();
        SDL_Rect srcRect = { rectPosition.first, rectPosition.second, rectSize.first, rectSize.second };
        SDL_Rect destRect = { x, y, _currentPixelSizeX, _currentPixelSizeY };

        SDL_RenderCopy(_renderer, _textureMap[textureName], &srcRect, &destRect);
    }

    void Window::displayTexts(ITexts *texts)
    {
        if (_renderer == nullptr)
            throw arcade::Error("SDL (Window) - displayTexts - Failed to display texts: Renderer is null.");

        if (!texts)
            throw arcade::Error("SDL (Window) - displayTexts - Failed to display texts: Texts object is null.");

        TextMap textMap = texts->getTextMap();

        int fontSize = _currentPixelSizeX;

        TTF_Font *tempFont = TTF_OpenFont("Fonts/arial.ttf", fontSize);

        if (!tempFont)
            throw arcade::Error("SDL (Window) - displayTexts - Failed to load font:" + std::string(TTF_GetError()));


        for (const auto &text : textMap) {
            int x = text.first.first * _currentPixelSizeX;
            int y = text.first.second * _currentPixelSizeY;
            std::string str = text.second.getStr();
            SDL_Color textColor = {
                (unsigned char)text.second.getRed(),
                (unsigned char)text.second.getGreen(),
                (unsigned char)text.second.getBlue(),
                (unsigned char)text.second.getAlpha()
            };
            if (str.size() == 0)
                continue;
            SDL_Surface *surface = TTF_RenderText_Solid(tempFont, str.c_str(), textColor);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
            int textWidth = surface->w;
            int textHeight = surface->h;

            SDL_FreeSurface(surface);

            SDL_Rect rect = { x, y, textWidth, textHeight };

            SDL_RenderCopy(_renderer, texture, nullptr, &rect);

            SDL_DestroyTexture(texture);
        }

        TTF_CloseFont(tempFont);
    }

    void Window::display()
    {
        if (_renderer == nullptr)
            throw arcade::Error("SDL (Window) - display - Failed to display: Renderer is null.");

        SDL_RenderPresent(_renderer);
    }

    Sdl2::Sdl2() :
        _pixels(nullptr),
        _texts(nullptr),
        _event(nullptr),
        _window(nullptr),
        _keyTable({
            {SDLK_UP, Key::UP_ARROW},
            {SDLK_DOWN, Key::DOWN_ARROW},
            {SDLK_LEFT, Key::LEFT_ARROW},
            {SDLK_RIGHT, Key::RIGHT_ARROW},
            {SDLK_BACKSPACE, Key::DELETE},
            {SDLK_RETURN, Key::ENTER},
            {SDLK_a, Key::A_KEY},
            {SDLK_b, Key::B_KEY},
            {SDLK_c, Key::C_KEY},
            {SDLK_d, Key::D_KEY},
            {SDLK_e, Key::E_KEY},
            {SDLK_f, Key::F_KEY},
            {SDLK_g, Key::G_KEY},
            {SDLK_h, Key::H_KEY},
            {SDLK_i, Key::I_KEY},
            {SDLK_j, Key::J_KEY},
            {SDLK_k, Key::K_KEY},
            {SDLK_l, Key::L_KEY},
            {SDLK_m, Key::M_KEY},
            {SDLK_n, Key::N_KEY},
            {SDLK_o, Key::O_KEY},
            {SDLK_p, Key::P_KEY},
            {SDLK_q, Key::Q_KEY},
            {SDLK_r, Key::R_KEY},
            {SDLK_s, Key::S_KEY},
            {SDLK_t, Key::T_KEY},
            {SDLK_u, Key::U_KEY},
            {SDLK_v, Key::V_KEY},
            {SDLK_w, Key::W_KEY},
            {SDLK_x, Key::X_KEY},
            {SDLK_y, Key::Y_KEY},
            {SDLK_z, Key::Z_KEY}
        }),
        _changeKeyTable({
            {SDLK_F1, ChangeKey::MAIN_MENU},
            {SDLK_F2, ChangeKey::PREV_GAME_LIB},
            {SDLK_F3, ChangeKey::NEXT_GAME_LIB},
            {SDLK_F4, ChangeKey::PREV_GRAPHICAL_LIB},
            {SDLK_F5, ChangeKey::NEXT_GRAPHICAL_LIB},
            {SDLK_ESCAPE, ChangeKey::ESCAPE},
        })
    {
    }

    Sdl2::~Sdl2() {}

    void Sdl2::init()
    {
        createEventObject();
        createWindowObject();

        if (TTF_Init() == -1)
            throw arcade::Error("SDL - init - Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));

        _window->openWindow(1920, 1000);
    }

    void Sdl2::stop()
    {
        TTF_Quit();
        _window->closeWindow();
    }

    std::string Sdl2::getName() const
    {
        return "Sdl2";
    }

    IEvent *Sdl2::getEventWrapper() const
    {
        return _event.get();
    }

    IWindow *Sdl2::getWindowWrapper() const
    {
        return _window.get();
    }

    void Sdl2::updatePixelsWrapper(IPixels *pixels)
    {
        _pixels = pixels;
    }

    void Sdl2::updateTextsWrapper(ITexts *texts)
    {
        _texts = texts;
    }

    void Sdl2::pollEvents()
    {
        SDL_Event e;

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                _window->closeWindow();
                continue;
            }
            if (e.type == SDL_KEYDOWN) {
                SDL_KeyCode currentKey = static_cast<SDL_KeyCode>(e.key.keysym.sym);

                if (_keyTable.contains(currentKey))
                    _event->pushEvent(_keyTable.at(currentKey));

                if (_changeKeyTable.contains(currentKey))
                    _event->pushChangeEvent(_changeKeyTable.at(currentKey));
                continue;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    _event->pushEvent(Key::MOUSE_BUTTON_LEFT, {e.button.x / std::max(1, static_cast<Window*>(_window.get())->getCurrentPixelSizeX()), e.button.y / std::max(1, static_cast<Window*>(_window.get())->getCurrentPixelSizeY())});
                } else if (e.button.button == SDL_BUTTON_RIGHT) {
                    _event->pushEvent(Key::MOUSE_BUTTON_RIGHT, {e.button.x / std::max(1, static_cast<Window*>(_window.get())->getCurrentPixelSizeX()), e.button.y / std::max(1, static_cast<Window*>(_window.get())->getCurrentPixelSizeY())});
                }
            }
        }
    }

    void Sdl2::display() const
    {
        _window->clearScreen();
        _window->displayPixels(_pixels);
        _window->displayTexts(_texts);
        _window->display();
    }

    IEvent *Sdl2::createEventObject()
    {
        _event = std::make_unique<Event>();
        return _event.get();
    }

    IWindow *Sdl2::createWindowObject()
    {
        _window = std::make_unique<Window>();
        return _window.get();
    }
}
