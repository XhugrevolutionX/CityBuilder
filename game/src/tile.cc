#include "tile.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "resource_manager.h"

Tile::Tile(const sf::Vector2f pos)
{
	tile = sf::Sprite(ResourceManager::Sprite(ResourceSprite::TextureType::kFloor));
	tile->setPosition(pos);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*tile, states);
}
