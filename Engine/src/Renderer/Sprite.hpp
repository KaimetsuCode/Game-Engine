#pragma once
#include "../Managers/TextureManager.hpp"
namespace Kaim { namespace Renderer
{
class Sprite
{
private:
    /* data */
    Kaim::Manager::TextureManager* textureManager;
    unsigned int VBO, VAO, EBO;
    void Init();
    std::string spriteName;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
public:
    Sprite(std::string name);
    Sprite(Kaim::Manager::TextureManager* textureManager, std::string name, std::string texturePath);
    void Render();
    void Update() {};
    ~Sprite();
};
}}