//
// Created by hugze on 21.06.2025.
//

#include "buildings/buildings_manager.h"

#include <SFML/System/Vector2.hpp>


namespace api::buildings {

void BuildingsManager::Add(BuildingsType type, sf::Vector2f position, ai::NpcManager* npcManager, TileMap* tilemap, RessourceManager* resourceManager){
  buildings_.emplace_back();
  tilemap->AddBuilding(position, type);

  buildings_.back().Setup(type, position, npcManager, tilemap, resourceManager);
}

void BuildingsManager::Update(float dt){
  for (auto& building : buildings_) {
    building.Update(dt);
  }
}
}