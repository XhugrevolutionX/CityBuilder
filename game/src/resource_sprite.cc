#include "resource_sprite.h"

void ResourceSprite::Setup()
{
	LoadTextures();
}

sf::Texture& ResourceSprite::GetTexture(TextureType resouce_id)
{
	if(static_cast<int>(resouce_id) < textures_.size())
	{
		return textures_.at(static_cast<int>(resouce_id));
	}
	return blank_texture_;
}

void ResourceSprite::LoadTextures()
{
	blank_texture_ = sf::Texture();
	if(!textures_.at(static_cast<int>(TextureType::kFloor)).loadFromFile("ressources/tile_0028.png"))
	{
	}
}
