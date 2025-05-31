#ifndef MAP_H
#define MAP_H
#include <vector>

#include "resource_sprite.h"
#include "tile.h"

class Tilemap : public sf::Drawable
{
	sf::Vector2u map_size_;

	std::vector<Tile> tiles_;
	sf::Vector2u size_sprit_;
    ResourceSprite resource_sprite_;

public:
	Tilemap();
	void SetTiles();
	void Setup(sf::Vector2u map_size);

	[[nodiscard]] sf::Vector2u SpritSize() const
	{
		return size_sprit_;
	}

	enum class TileType
	{
		HERBE = 0,
		SOL = 1,
		MUR = 2
	};

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif //MAP_H
