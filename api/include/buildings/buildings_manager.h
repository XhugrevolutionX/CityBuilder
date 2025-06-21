//
// Created by hugze on 21.06.2025.
//

#ifndef BUILDINGS_MANAGER_H
#define BUILDINGS_MANAGER_H

#include "building.h"

namespace api::buildings{

enum class BuildingsColor {
  kCyan,
  kRed,
  kLime,
  kPurple
};

enum class BuildingsType {
  kMine,
  kLumber
};

class BuildingsManager {

  std::vector<Building> buildings_;

public:
  void Add(BuildingsType type, BuildingsColor color, sf::Vector2f position, TileMap* tilemap);
  void Update(float dt);
  void Draw(sf::RenderWindow &window);

};
}


#endif //BUILDINGS_MANAGER_H
