#ifndef RESOURCE_MANGER_H
#define RESOURCE_MANGER_H
#include "resource_sprite.h"

namespace ResourceManager
{
	void Setup();
	sf::Texture& Sprite(ResourceSprite::TextureType type);
}
#endif //RESOURCE_MANGER_H
