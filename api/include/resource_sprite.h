#ifndef RESOURCE_SPRITE_H
#define RESOURCE_SPRITE_H
#include <array>
#include <SFML/Graphics/Texture.hpp>

class ResourceSprite
{
public:
	enum class TextureType
	{
		kFloor,
		kMax
	};
    std::string groundSpritePath = "../ressources/MiniWorld/MiniWorldSprites/Ground/Sand1.png";

	void Setup();
	sf::Texture& GetTexture(TextureType resource_id);

private:
	std::array<sf::Texture, static_cast<int>(TextureType::kMax)> textures_;
	sf::Texture blank_texture_;
	void LoadTextures();
};
#endif //RESOURCE_SPRITE_H
