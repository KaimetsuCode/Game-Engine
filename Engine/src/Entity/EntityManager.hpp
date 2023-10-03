#pragma once

#include <vector>
#include "Entity.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Managers/TextureManager.hpp"

class EntityManager {
private:
    std::vector<Entity*> entities;
public:
    EntityManager();
    Entity* AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);
    void Update();
    void Render();
    ~EntityManager();
};