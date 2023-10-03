#include "TextureManager.hpp"

namespace Kaim { namespace Manager {
    TextureManager::TextureManager() {
        INFO("Texture Manager Created");
    }
    TextureManager::~TextureManager() {
        INFO("Texture Manager Destroyed");
    }

    void TextureManager::LoadTexture(std::string name, std::string path) {
        for(auto const& [key, val] : textures) {
            if (val.path == path) {
                WARNING("Texture with path %s already exists", path.c_str());
                return;
            }
            if(key == name) {
                WARNING("Texture with name %s already exists", name.c_str());
                return;
            }
        }

        SDL_Surface* surface = IMG_Load(path.c_str());
        if (surface == NULL) {
            ERROR("Failed to load image: %s", IMG_GetError());
            return;
        }
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        // get number of channels in the SDL surface
        GLint nOfColors = surface->format->BytesPerPixel;
        unsigned int format;

        if (nOfColors == 4)     // contains an alpha channel
        {
                if (surface->format->Rmask == 0x000000ff)
                        format = GL_RGBA;
                else
                        format = GL_BGRA;
        } else if (nOfColors == 3)     // no alpha channel
        {
                if (surface->format->Rmask == 0x000000ff)
                        format = GL_RGB;
                else
                        format = GL_BGR;
        } else {
                ERROR("Image is not truecolor");
                return;
        }
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
        
        glGenerateMipmap(GL_TEXTURE_2D);
        SDL_FreeSurface(surface);

        Texture textureStruct;
        textureStruct.id = texture;
        textureStruct.path = path;
        textures[name] = textureStruct;
    }
    void TextureManager::Bind(std::string path) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[path].id);
    }
    void TextureManager::Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}}