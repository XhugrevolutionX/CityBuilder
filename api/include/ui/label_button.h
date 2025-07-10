//
// Created by hugze on 10.07.2025.
//

#ifndef LABEL_BUTTON_H
#define LABEL_BUTTON_H

namespace api::ui {
class LabelButton : public Button {
  sf::Text prices_label_;
 public:
  LabelButton(sf::Vector2f pos, std::string_view label, std::string_view prices_label, const sf::Texture &t,
              const sf::Texture &hover_t, const sf::Font &font): Button(pos, label, t, hover_t, font), prices_label_(font) {

    prices_label_.setPosition({pos.x, pos.y - 25.f});
    prices_label_.setCharacterSize(24);
    prices_label_.setFillColor(sf::Color(0, 0, 0, 0));
    prices_label_.setString(std::string(prices_label));

    OnHoverEnter = [this]() {
      SetHoverState(true);
      prices_label_.setFillColor(sf::Color(0, 0, 0, 255));
    };
    OnHoverExit = [this]() {
      SetHoverState(false);
      prices_label_.setFillColor(sf::Color(0, 0, 0, 0));
    };

  }

  void Draw(sf::RenderWindow &window) const;
};

inline void LabelButton::Draw(sf::RenderWindow &window) const {

    Button::Draw(window);
    window.draw(prices_label_);
  }
}// namespace api::ui
#endif  // LABEL_BUTTON_H
