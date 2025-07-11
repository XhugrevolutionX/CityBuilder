//
// Created by hugze on 11.07.2025.
//

#ifndef CURSOR_INDICATOR_H
#define CURSOR_INDICATOR_H
#include <SFML/Graphics/RenderWindow.hpp>

#include "buildings/buildings_manager.h"
#include "graphics/tilemap.h"

namespace api::ui {

class CursorIndicator {
    sf::Vector2f position_;
    sf::Texture texture_;

public:

    CursorIndicator() = default;

    void SetTexture(sf::Texture texture);
    void SetPosition(sf::Vector2f pos);
    void Draw(sf::RenderWindow& window) const;

};
}

#endif //CURSOR_INDICATOR_H
