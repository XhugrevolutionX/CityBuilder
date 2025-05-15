#include "game.h"
#include <SFML/Graphics.hpp>

namespace game
{
  namespace
  {
    sf::RenderWindow          window_;

    sf::Texture               texture_("ressources/image_test.jpg");
    std::optional<sf::Sprite> sprite_;
  }

  void Setup()
  {
    sprite_ = sf::Sprite(texture_);
    window_.create(sf::VideoMode(sf::Vector2u(sprite_->getGlobalBounds().size.x, sprite_->getGlobalBounds().size.y)), "SFML works!");
  }

  void UpdateMap()
  {
    window_.clear();
    window_.draw(*sprite_);
    window_.display();
  }
  
  void Run()
  {
    Setup();

    while(window_.isOpen()) {
      while(const std::optional event = window_.pollEvent())
      {
        if(event->is<sf::Event::Closed>()) window_.close();
      }

      UpdateMap();
    }
  }
}
