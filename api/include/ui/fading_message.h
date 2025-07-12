//
// Created by hugze on 12.07.2025.
//

#ifndef FADING_MESSAGE_H
#define FADING_MESSAGE_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace api::ui {

class FadingMessage {

  sf::Text text_;
  float counter_ = 0.f;
  float time_limit_ = 2.f;
  bool visible_ = true;


public:

  FadingMessage(const sf::Font& font, const std::string& text, sf::Vector2f pos);
  void Update(float dt);
  void Draw(sf::RenderWindow& window) const;
  bool Visible() const {return visible_;}

};
}

#endif //FADING_MESSAGE_H
