//
// Created by hugze on 21.06.2025.
//

#include "buildings/building.h"

#include <iostream>

namespace api::buildings {

void Building::Setup(BuildingsType type, sf::Vector2f position) {
  position_  = position;
  type_ = type;
}

void Building::Update(float dt) {
  throw std::runtime_error("Not implemented");
}
}
