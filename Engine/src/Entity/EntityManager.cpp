#include "EntityManager.hpp"

EntityManager::EntityManager() {
    INFO("Entity Manager Created");
}

EntityManager::~EntityManager() {
    INFO("Entity Manager Destroyed");
    // delete all entities
    for (auto& entity : entities) {
        entity = nullptr;
        delete entity;
    }
}

Entity* EntityManager::AddEntity(Entity* entity) {
    entities.push_back(entity);
    return entity;
}

void EntityManager::RemoveEntity(Entity* entity) {
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        if (*it == entity) {
            entities.erase(it);
            delete entity;
            return;
        }
    }
}

void EntityManager::Update() {
    for (auto const& entity : entities) {
        entity->Update();
    }
}

void EntityManager::Render() {
    for (auto const& entity : entities) {
        entity->Render();
    }
}