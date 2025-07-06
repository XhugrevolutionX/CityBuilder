#ifndef STOCK_H
#define STOCK_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "ressources/ressource.h"

#endif //STOCK_H

namespace api::ui {

  class Stock {
    int quantity_ = 0;
    ressource::RessourcesType type_;
    sf::Font font_;
    sf::Text display_;

  public:
    void UpdateDisplay();
    Stock(ressource::RessourcesType type);
    void AddQuantity(int quantity);
    void RemoveQuantity(int quantity);
    void Draw(sf::RenderWindow &window) const;
  };
}