//
// Created by hugze on 21.06.2025.
//

#include "buildings/buildings_manager.h"

#include <SFML/System/Vector2.hpp>

#include "buildings/buildings_factory.h"

namespace api::buildings {

void BuildingsManager::Add(BuildingsType type, sf::Vector2f position, TileMap* tilemap){
  CreateBuilding(buildings_, type, position, tilemap);
}

void BuildingsManager::Update(float dt){
  for (auto& building : buildings_) {
    building.Update(dt);
  }
}

void BuildingsManager::Draw(sf::RenderWindow &window){
  for (auto& building : buildings_) {
    building.Draw(window);
  }
}

}