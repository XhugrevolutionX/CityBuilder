//
// Created by hugze on 21.06.2025.
//

#ifndef BUILDINGS_MANAGER_H
#define BUILDINGS_MANAGER_H

#include "building.h"

namespace api::buildings{

enum class BuildingsType {
  kMine,
  kLumber,
  kWindmill,
  kNone
};

class BuildingsManager {

private:
  std::vector<Building> buildings_;

public:
  void Add(BuildingsType type, sf::Vector2f position, ai::NpcManager* npcManager, TileMap* tilemap, ResourceManager* resourceManager);
  void Update(float dt);

  std::vector<Building>& GetBuildings(){ return buildings_; }
};
}


#endif //BUILDINGS_MANAGER_H
