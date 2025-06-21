//
// Created by hugze on 21.06.2025.
//

#ifndef BUILDINGS_FACTORY_H
#define BUILDINGS_FACTORY_H
#include "buildings_manager.h"

namespace api::buildings {
inline void CreateBuilding(std::vector<Building> &buildings, BuildingsType type, sf::Vector2f position, TileMap *tilemap){
  buildings.emplace_back();

  tilemap->AddBuilding(position);

  switch (type) {

    case BuildingsType::kMine:
        buildings.back().Setup("mine.png",position, tilemap);
      break;

    case BuildingsType::kLumber:
        buildings.back().Setup("lumber_house.png",position, tilemap);
      break;

    case BuildingsType::kWindmill:
        buildings.back().Setup("windmill.png",position, tilemap);
      break;

    default:
      break;
  }
}
}

#endif //BUILDINGS_FACTORY_H
