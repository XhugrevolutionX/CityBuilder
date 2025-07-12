//
// Created by hugze on 12.07.2025.
//

#include "ui/fading_message.h"

namespace api::ui {

FadingMessage::FadingMessage(const sf::Font& font, const std::string& text, sf::Vector2f pos, sf::Color color): text_(font, text, 15) {
  text_.setPosition(pos - text_.getGlobalBounds().getCenter());
  color_ = color;
  text_.setFillColor(color_);
}

void FadingMessage::Update(float dt) {
  counter_ += dt;
  text_.setFillColor(sf::Color(color_.r, color_.g, color_.b, color_.a - 255 * (counter_ / time_limit_ )));
  text_.setPosition(text_.getPosition() - sf::Vector2f(0, 20 * dt));
  if (counter_ > time_limit_) {
    counter_ = 0.f;
    visible_ = false;
  }
}

void FadingMessage::Draw(sf::RenderWindow& window) const {
  window.draw(text_);
}
}  // namespace api::ui