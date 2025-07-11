//
// Created by hugze on 11.07.2025.
//

#include "ui/cursor_indicator.h"

namespace api::ui {

void CursorIndicator::SetTexture(sf::Texture texture) {texture_ = texture;}

void CursorIndicator::SetPosition(sf::Vector2f pos) {position_ = pos;}

void CursorIndicator::Draw(sf::RenderWindow& window) const {
  sf::Sprite sprite(texture_);
  sprite.setPosition(position_);

  window.draw(sprite);

}
}