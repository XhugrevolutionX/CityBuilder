//
// Created by hugze on 21.06.2025.
//

#include "buildings/building.h"

#include <iostream>

namespace api::buildings {

void Building::Setup(std::string_view filename, sf::Vector2f position, TileMap* tileMap) {
  if(!texture_.loadFromFile("_assets/sprites/" + std::string(filename))) {
    std::cout << "Error loading texture " << filename << std::endl;
    if (!texture_.loadFromFile("_assets/sprites/empty.png")) {
      std::cout << "Error loading texture empty.png" << std::endl;
    }
  }

  position_ = position;
  tileMap_ = tileMap;
};
void Building::Update(float dt) {
  throw std::runtime_error("Not implemented");
};

void Building::Draw(sf::RenderWindow &window) {
  sf::Sprite sprite(texture_);
  sprite.setPosition(position_);
  window.draw(sprite);
};

}
