#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

namespace Kaim { namespace Manager {
    struct Texture {
        unsigned int id;
        std::string path;
    };

    class TextureManager {
        // TODO: Make this a singleton
        private:
            std::map<std::string, Texture> textures;
        public:
            TextureManager();
            ~TextureManager();

            void LoadTexture(std::string name, std::string path);
            void Bind(std::string name);
            void Unbind();
    };
}}