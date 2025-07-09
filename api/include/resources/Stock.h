#ifndef STOCK_H
#define STOCK_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "resources/resources.h"


namespace api::resources {

  class Stock {
    int quantity_ = 0;
    ResourcesType type_;
    sf::Font font_;
    sf::Text display_;

  public:
    void UpdateDisplay();
    Stock(ResourcesType type, int quantity);
    int GetQuantity() const;
    void AddQuantity(int quantity);
    void RemoveQuantity(int quantity);
    void Draw(sf::RenderWindow &window) const;
  };
}

#endif //STOCK_H