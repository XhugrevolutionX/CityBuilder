//
// Created by hugze on 21.06.2025.
//

#ifndef BUILDINGS_MANAGER_H
#define BUILDINGS_MANAGER_H

#include "building.h"
#include "resources/prices.h"

namespace api::buildings{

enum class BuildingsType {
  kMine,
  kLumber,
  kWindmill,
  kNone
};

class BuildingsManager {

  std::vector<Building> buildings_;
  std::vector<resources::Prices> prices_;

public:
  void SetupPrices();
  void Add(BuildingsType type, sf::Vector2f position, ai::NpcManager* npcManager, TileMap* tilemap, ResourceManager* resourceManager, resources::StockManager* stock_manager);
  void Update(float dt);
  void Reset();
  std::pair<int, int> GetPrice(BuildingsType type);

  std::vector<Building>* GetBuildings(){ return &buildings_; }
};
}

#endif //BUILDINGS_MANAGER_H
