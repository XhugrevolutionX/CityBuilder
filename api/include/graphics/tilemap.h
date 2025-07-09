#ifndef API_GRAPHICS_TILEMAP_H
#define API_GRAPHICS_TILEMAP_H

#include <SFML/Graphics.hpp>

#include "assets/asset_manager.h"
#include "resources/resources.h"
#include "ui/clickable.h"

namespace api::buildings {
enum class BuildingsType;
}
constexpr int kWidth = 1600;
constexpr int kHeight = 900;
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
        kFood,
        kMine,
        kLumber,
        kWindmill,
        kLength
    };
private:
    std::string_view files[static_cast<size_t>(Tile::kLength)] {
        "empty.png", "grass.png", "water.png", "maison.png", "rock.png", "tree.png", "wheat.png", "mine.png", "lumber_house.png", "windmill.png"
    };

    std::array<Tile, kWidth/kPixelStep * kHeight/kPixelStep> tiles_ = {};
    std::array<Tile, kWidth/kPixelStep * kHeight/kPixelStep> ressources_ = {};
    std::array<Tile, kWidth/kPixelStep * kHeight/kPixelStep> buildings_ = {};
    AssetManager<sf::Texture, Tile, "_assets/sprites"> textures;


    std::vector<sf::Vector2f> walkables_;

public:
    static sf::Vector2f ScreenPosition(int index);
    static sf::Vector2f TilePos(sf::Vector2i);
    static float Distance(sf::Vector2f p1, sf::Vector2f p2);
    static int Index(sf::Vector2f screenPosition);


    void Setup();
    void Draw(sf::RenderWindow &window);
    void SetResourcesTile(int, Tile);
    void SetTile(int, Tile);
    std::vector<sf::Vector2f> NearResources(api::resources::ResourcesType type, sf::Vector2f pos, sf::Vector2f dist);

    void AddBuilding(sf::Vector2f position, api::buildings::BuildingsType type);

    std::vector<sf::Vector2f> GetWalkables() const;
    std::vector<int> GetCollectibles(Tile);
    std::vector<sf::Vector2f> GetHouses() const;
    static int GetStep() {return kPixelStep;}
    static sf::Vector2u GetSize() {return {kWidth, kHeight};}
    Tile GetGroundType(int index);
};
#endif
