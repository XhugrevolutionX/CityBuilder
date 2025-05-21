#include "tilemap.h"

#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

Tilemap::Tilemap()
{
	size_sprit_ = sf::Vector2u(sf::Texture("ressources/tile_0028.png").getSize());
}

void Tilemap::Setup(const sf::Vector2u map_size)
{
	map_size_ = map_size;
    tiles_.reserve(map_size_.x * map_size_.y);
}

void Tilemap::SetTiles()
{
	tiles_.clear();
	for(int x = 0; x < map_size_.x; x++)
	{
		for(int y = 0; y < map_size_.y; y++)
		{
			tiles_.emplace_back(sf::Vector2f(x * SpritSize().x, y * SpritSize().y));
		}
	}
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const auto& tile : tiles_)
	{
		target.draw(tile, states);
	}
}
