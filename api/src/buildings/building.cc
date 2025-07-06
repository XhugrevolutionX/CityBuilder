//
// Created by hugze on 21.06.2025.
//

#include "buildings/building.h"

#include <iostream>

#include "ai/npc_manager.h"
#include "buildings/buildings_manager.h"

namespace api::buildings {
void Building::Setup(BuildingsType type, sf::Vector2f position, ai::NpcManager* npcManager, TileMap* tilemap, ResourceManager* resourceManager) {
  position_  = position;
  type_ = type;
  npcManager_ = npcManager;
  tilemap_ = tilemap;
  resourceManager_ = resourceManager;

  SummonNpc();
}

void Building::Update(float dt) {

}

void Building::SummonNpc() {
  switch (type_) {
    case BuildingsType::kLumber :
      npcManager_->Add(ai::NpcType::kCyan, this->position_, tilemap_, resourceManager_);
      break;
    case BuildingsType::kMine :
      npcManager_->Add(ai::NpcType::kRed, this->position_, tilemap_, resourceManager_);
      break;
    case BuildingsType::kWindmill :
      npcManager_->Add(ai::NpcType::kLime, this->position_, tilemap_, resourceManager_);
      break;
    case BuildingsType::kNone :
      break;
  }

}
}
