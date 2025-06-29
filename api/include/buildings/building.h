//
// Created by hugze on 21.06.2025.
//

#ifndef BUILDING_H
#define BUILDING_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "graphics/tilemap.h"

namespace api::buildings {
class Building {

  sf::Vector2f position_;
  BuildingsType type_;

public:
  void Setup(BuildingsType type, sf::Vector2f position);
  void Update(float dt);

};}


#endif //BUILDING_H
