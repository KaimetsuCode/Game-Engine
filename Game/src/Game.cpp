
#include <iostream>
#include <Window/Window.hpp>
#include <Shaders/Shader.hpp>
#include <Managers/TextureManager.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Renderer/Sprite.hpp>


int main(int argc, char* argv[]) {
    Kaim::Window window("Game", 1080, 720);

    Kaim::Shader shader("Assets/shaders/basic/vertex.glsl", "Assets/shaders/basic/fragment.glsl");
    Kaim::Manager::TextureManager textureManager;

        float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    textureManager.LoadTexture("box", "Assets/images/Box.jpg");


    Kaim::Renderer::Sprite sprite(&textureManager, "box2", "Assets/images/Box.png");
    while (window.IsOpen()) {

    
        GLenum error = glGetError();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                window.Close();
            }
        }

        window.Update(0.2f, 0.3f, 0.3f, 1.0f);
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f));
        transform = glm::rotate(transform, (float)SDL_GetTicks() / 1000.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));

        shader.use();
        shader.setMat4("transform", transform);
        textureManager.Bind("box");
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        shader.use();

        glm::mat4 transform2 = glm::mat4(1.0f);
        transform2 = glm::translate(transform2, glm::vec3(0.5f, 0.5f, 0.0f));
        transform2 = glm::rotate(transform2, (float)SDL_GetTicks() / 1000.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        transform2 = glm::scale(transform2, glm::vec3(0.5f, 0.5f, 0.5f));

        shader.setMat4("transform", transform2);

        sprite.Render();
        window.Render();
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}