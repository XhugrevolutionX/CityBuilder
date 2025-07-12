//
// Created by hugze on 21.06.2025.
//

#include "buildings/buildings_manager.h"

#include <SFML/System/Vector2.hpp>

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif // TRACY_ENABLE

namespace api::buildings {

void BuildingsManager::SetupPrices() {

  resources::Prices null_prices;
  resources::Prices lumber_prices;
  resources::Prices mine_prices;
  resources::Prices windmill_prices;

  null_prices.init(0,0,0);
  lumber_prices.init(50,50,0);
  mine_prices.init(100, 50,0);
  windmill_prices.init(200, 100,0);

  prices_.push_back(null_prices);
  prices_.push_back(lumber_prices);
  prices_.push_back(mine_prices);
  prices_.push_back(windmill_prices);
}



void BuildingsManager::Add(BuildingsType type, sf::Vector2f position, ai::NpcManager* npcManager, TileMap* tilemap, ResourceManager* resourceManager, resources::stock_manager* stock_manager){

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
std::pair<int, int> BuildingsManager::GetPrice(BuildingsType type) {
  switch (type) {
    case BuildingsType::kLumber:
      return prices_[1].GetPrice();
    case BuildingsType::kMine:
      return prices_[2].GetPrice();
    case BuildingsType::kWindmill:
      return prices_[3].GetPrice();
    case BuildingsType::kNone:
      return prices_[0].GetPrice();
  }
  return prices_[0].GetPrice();
}
}  // namespace api::buildings