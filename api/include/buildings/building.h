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

  sf::Texture texture_;
  const TileMap* tileMap_;
  sf::Vector2f position_;

public:
  void Setup(std::string_view filename, sf::Vector2f position, TileMap* tileMap);
  void Update(float dt);

  void Draw(sf::RenderWindow &window);

};}


#endif //BUILDING_H
