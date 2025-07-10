#include "resources/Stock.h"

#include <SFML/Graphics/Font.hpp>

namespace api::resources {

Stock::Stock(ResourcesType type, int quantity) : display_(font_) {
  quantity_ = quantity;
  type_ = type;

  if (!font_.openFromFile("_assets/fonts/BKANT.TTF")) {
    // handle error
  }

  display_.setFont(font_);
  display_.setCharacterSize(30);
  display_.setFillColor(sf::Color::Black);

  UpdateDisplay();
}

int Stock::GetQuantity() const {return quantity_;}

void Stock::AddQuantity(int quantity) {
  quantity_ += quantity;
  UpdateDisplay();
}

void Stock::RemoveQuantity(int quantity) {
  quantity_ -= quantity;
  UpdateDisplay();
}

void Stock::UpdateDisplay() {
  switch (type_) {
    case ResourcesType::kWood:
      display_.setString("Wood : " + std::to_string(quantity_));
      display_.setPosition({10, 0});
      break;

    case ResourcesType::kStone:
      display_.setString("Stone : " + std::to_string(quantity_));
      display_.setPosition({10, 30});
      break;

    case ResourcesType::kFood:
      display_.setString("Food : " + std::to_string(quantity_));
      display_.setPosition({10, 60});
      break;

    case ResourcesType::kNone:
      display_.setString("");
      display_.setPosition({0, 0});
      break;
  }
}



void Stock::Draw(sf::RenderWindow &window) const {
  window.draw(display_);
}

}