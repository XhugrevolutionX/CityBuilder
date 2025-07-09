//
// Created by hugze on 21.06.2025.
//

#include "buildings/buildings_manager.h"

#include <SFML/System/Vector2.hpp>

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif // TRACY_ENABLE

namespace api::buildings {

void BuildingsManager::Add(BuildingsType type, sf::Vector2f position, ai::NpcManager* npcManager, TileMap* tilemap, ResourceManager* resourceManager, resources::StockManager* stock_manager){

  buildings_.emplace_back();
  tilemap->AddBuilding(position, type);

  buildings_.back().Setup(type, position, npcManager, tilemap, resourceManager, stock_manager);
}

void BuildingsManager::Update(float dt) {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif  // TRACY_ENABLE
  for (auto& building : buildings_) {
    building.Update(dt);
  }
}
sf::Vector2i BuildingsManager::GetPrice(BuildingsType type) {
  switch (type) {
    case BuildingsType::kLumber:
      return {50,0};
    case BuildingsType::kMine:
      return {100, 0};
    case BuildingsType::kWindmill:
      return {200, 100};
    case BuildingsType::kNone:
      return {0,0};
  }
  return {0,0};
}
}  // namespace api::buildings