#ifndef TILES_H
#define TILES_H
#include <optional>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>


class Tile : public sf::Drawable
{
private:
	std::optional<sf::Sprite> tile;

public:
	Tile(sf::Vector2f pos);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif //TILES_H
