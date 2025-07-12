//
// Created by hugze on 12.07.2025.
//

#include "ui/fading_message.h"

namespace api::ui {

FadingMessage::FadingMessage(const sf::Font& font, const std::string& text, sf::Vector2f pos): text_(font, text, 15) {
  text_.setPosition(pos - text_.getGlobalBounds().getCenter());
  text_.setFillColor(sf::Color(0, 0, 0, 0));
}

void FadingMessage::Update(float dt) {
  counter_ += dt;
  text_.setFillColor(sf::Color(0, 0, 0, 255 - 255 * (counter_ / time_limit_ )));
  if (counter_ > time_limit_) {
    counter_ = 0.f;
    visible_ = false;
  }
}

void FadingMessage::Draw(sf::RenderWindow& window) const {
  window.draw(text_);
}
}  // namespace api::ui