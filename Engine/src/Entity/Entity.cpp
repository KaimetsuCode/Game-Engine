#include "Entity.hpp"

int Entity::uid = 0;

Entity::Entity(/* args */)
{
    id = uid++;
}

void Entity::Rotate(float speed, glm::vec3 axis) {
    transform = glm::rotate(transform, glm::radians(speed), axis);
}

void Entity::Translate(glm::vec3 translation) {
    transform = glm::translate(transform, translation);
}

void Entity::Scale(glm::vec3 scale) {
    transform = glm::scale(transform, scale);
}

glm::mat4& Entity::GetTransform() {
    return transform;
}