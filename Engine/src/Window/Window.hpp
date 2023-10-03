#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

namespace Kaim {
    class Window {
        private:
            SDL_Window* window;
            SDL_GLContext context;
            int width;
            int height;
            bool open;
        public:
            Window(std::string title, int width, int height);
            SDL_Window* GetWindow();
            void Update(float r, float g, float b, float a);
            void Render();
            bool IsOpen();
            void Close();
            ~Window();
    };
}