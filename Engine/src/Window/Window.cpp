#include "Window.hpp"

namespace Kaim {
    Window::Window(std::string title, int width, int height) {
        SDL_Init(SDL_INIT_EVERYTHING);
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        this->width = width;
        this->height = height;
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
        if (window == NULL) {
            ERROR("Failed to create window: %s", SDL_GetError());
            open = false;
            return;
        } 
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        context = SDL_GL_CreateContext(window);
        if (glewInit() != GLEW_OK) {
            ERROR("OpenGL Could not Initalize");
            open = false;
        }

        glewExperimental = GL_TRUE;

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glViewport(0, 0, width, height);

        open = true;
    }
    void Window::Update(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void Window::Render() {
        SDL_GL_SwapWindow(window);
    }

    SDL_Window* Window::GetWindow() {
        return this->window;
    }
    bool Window::IsOpen() {
        return this->open;
    }
    void Window::Close() {
        this->open = false;
    }

    Window::~Window() {
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(this->window);
        IMG_Quit();
        SDL_Quit();
    }
}