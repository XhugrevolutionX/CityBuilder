#include "resource_sprite.h"

namespace ResourceManager
{
	namespace
	{
		ResourceSprite resource_sprite;
	}

	void Setup()
	{
		resource_sprite.Setup();
	}

	sf::Texture& Sprite(const ResourceSprite::TextureType type)
	{
		return resource_sprite.GetTexture(type);
	}
}
