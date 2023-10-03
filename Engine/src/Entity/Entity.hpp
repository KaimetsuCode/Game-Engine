#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity
{
private:
    glm::mat4 transform = glm::mat4(1.0f);
    int id;
public:
    static int uid;
    Entity(/* args */);
    void Rotate(float speed, glm::vec3 axis);
    void Translate(glm::vec3 translation);
    void Scale(glm::vec3 scale);
    glm::mat4& GetTransform();

    KAIM_INLINE int GetId() { return id; }

public:
    void Update() {}
    void Render() {}
    ~Entity();
};