//
// Created by hugze on 21.06.2025.
//

#ifndef BUILDINGS_FACTORY_H
#define BUILDINGS_FACTORY_H
#include "buildings_manager.h"

namespace api::buildings {
inline void CreateBuilding(std::vector<Building> &buildings, BuildingsType type, BuildingsColor color, sf::Vector2f position, TileMap *tilemap){
  buildings.emplace_back();

  tilemap->AddBuilding(position);

  switch (type) {

    case BuildingsType::kMine:

      switch (color) {
      case BuildingsColor::kCyan:
          buildings.back().Setup("mine_cyan.png",position, tilemap);
          break;
      case BuildingsColor::kRed:
          buildings.back().Setup("mine_red.png",position, tilemap);
          break;
      case BuildingsColor::kLime:
          buildings.back().Setup("mine_lime.png",position, tilemap);
          break;
      case BuildingsColor::kPurple:
          buildings.back().Setup("mine_purple.png",position, tilemap);
          break;
      default:
          break;
      }

      break;

    case BuildingsType::kLumber:

      switch (color) {
      case BuildingsColor::kCyan:
          buildings.back().Setup("lumber_house_cyan.png",position, tilemap);
          break;
      case BuildingsColor::kRed:
          buildings.back().Setup("lumber_house_red.png",position, tilemap);
          break;
      case BuildingsColor::kLime:
          buildings.back().Setup("lumber_house_lime.png",position, tilemap);
          break;
      case BuildingsColor::kPurple:
          buildings.back().Setup("lumber_house_purple.png",position, tilemap);
          break;
      default:
          break;
      }

      break;

    default:
      break;
  }
}
}

#endif //BUILDINGS_FACTORY_H
