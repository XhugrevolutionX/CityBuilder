﻿//
// Created by hugze on 21.06.2025.
//

#ifndef BUILDING_H
#define BUILDING_H

#include <SFML/System/Vector2.hpp>

#include "ai/npc_manager.h"
#include "graphics/tilemap.h"

namespace api::buildings {
class Building {

  sf::Vector2f position_;
  BuildingsType type_;
  ai::NpcManager* npcManager_;
  TileMap* tilemap_;
  ResourceManager* resourceManager_;
  resources::StockManager* stocks_;

public:
  void Setup(BuildingsType type, sf::Vector2f position, ai::NpcManager* npcManager, TileMap* tilemap, ResourceManager* resourceManager, resources::StockManager* stock_manager);
  void Update(float dt);
  void SummonNpc();
  BuildingsType GetType() const { return type_; }

};}


#endif //BUILDING_H
