﻿#ifndef API_GRAPHICS_TILEMAP_H
#define API_GRAPHICS_TILEMAP_H

#include <SFML/Graphics.hpp>

#include "assets/asset_manager.h"
#include "ui/clickable.h"

namespace api::buildings {
enum class BuildingsType;
}
constexpr int kWidth = 1600;
constexpr int kHeight = 1280;
constexpr int kPixelStep = 16;
constexpr double perlinThreshold = 0.7;

using core::experimental::AssetManager;


class TileMap : public api::ui::Clickable{

public:
    enum class Tile {
        kEmpty,
        kGrass,
        kWater,
        kMaison,
        kRock,
        kTree,
        kMine,
        kLumber,
        kWindmill,
        kLength
    };
private:
    std::string_view files[static_cast<size_t>(Tile::kLength)] {
        "empty.png", "grass.png", "water.png", "maison.png", "rock.png", "tree.png", "mine.png", "lumber_house.png", "windmill.png"
    };

private:
    std::array<Tile, kWidth/kPixelStep * kHeight/kPixelStep> tiles_ = {};
    std::array<Tile, kWidth/kPixelStep * kHeight/kPixelStep> ressources_ = {};
    std::array<Tile, kWidth/kPixelStep * kHeight/kPixelStep> buildings_ = {};
    AssetManager<sf::Texture, Tile, "_assets/sprites"> textures;

    static int Index(sf::Vector2f screenPosition);

    std::vector<sf::Vector2f> walkables_;

public:
    static sf::Vector2f ScreenPosition(int index);
    static sf::Vector2f TilePos(sf::Vector2i);

    void Setup();
    void Draw(sf::RenderWindow &window);
    void SetTile(int, Tile);

    void AddBuilding(sf::Vector2f position, api::buildings::BuildingsType type);

    std::vector<sf::Vector2f> GetWalkables() const;
    std::vector<int> GetCollectibles(Tile);
    std::vector<sf::Vector2f> GetHouses() const;
};
#endif
