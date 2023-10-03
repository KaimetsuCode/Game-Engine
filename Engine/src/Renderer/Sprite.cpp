#include "Sprite.hpp"

namespace Kaim { namespace Renderer
{
    Sprite::Sprite(Kaim::Manager::TextureManager* textureManager, std::string name) {
        spriteName = name;
        this->Init();
        textureManager = textureManager;
    }

    void Sprite::Init() {
        vertices = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
        };
        indices = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), &indices.front(), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    Sprite::Sprite(Kaim::Manager::TextureManager* textureManager, std::string name, std::string texturePath) {
        this->textureManager = textureManager;
        spriteName = name;
        textureManager->LoadTexture(name, texturePath);
        this->Init();
    }

    void Sprite::Render() {
        glBindVertexArray(VAO);
        textureManager->Bind(spriteName);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        textureManager->Unbind();
    }

    Sprite::~Sprite() {
        delete textureManager;
    }
}
}