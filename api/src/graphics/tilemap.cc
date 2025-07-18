//
// Created by sebas on 15/05/2025.
//
#include "graphics/tilemap.h"

#include <noise/noise.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <random>

#include "buildings/buildings_manager.h"
#include "resources/resources.h"
#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif // TRACY_ENABLE

void TileMap::Perlin() {

  noise::module::Perlin perlin;

  perlin.SetSeed(150);       // Set seed for reproducibility
  perlin.SetFrequency(5);    // Controls the "zoom" level
  perlin.SetPersistence(1);  // Amplitude of successive octaves
  perlin.SetLacunarity(1);   // Frequency multiplier between octaves
  perlin.SetOctaveCount(2);  // Number of octaves (layers of detail)
  perlin.SetNoiseQuality(
      noise::QUALITY_STD);  // QUALITY_FAST, QUALITY_STD, or QUALITY_BEST

  for (int i = 0; i < kHeight / kPixelStep; i++) {
    for (int j = 0; j < kWidth / kPixelStep; j++) {
      double xi = static_cast<double>(j) / 100;
      double xj = static_cast<double>(i) / 100;

      double raw = perlin.GetValue(xi, xj, 0.0);
      double value = (raw + 1.0) / 2.0;

      int idx = (j) + ((i)*kWidth / kPixelStep);
      if (value < perlinThreshold) {
        tiles_[idx] = Tile::kGrass;

        walkables_.push_back(ScreenPosition(idx));
      } else {
        tiles_[idx] = Tile::kWater;
      }
    }
  }

  perlin.SetSeed(50);          // Set seed for reproducibility
  perlin.SetFrequency(5);      // Controls the "zoom" level
  perlin.SetPersistence(0.3);  // Amplitude of successive octaves
  perlin.SetLacunarity(2);     // Frequency multiplier between octaves
  perlin.SetOctaveCount(3);    // Number of octaves (layers of detail)
  perlin.SetNoiseQuality(
      noise::QUALITY_STD);  // QUALITY_FAST, QUALITY_STD, or QUALITY_BEST

  for (auto element : walkables_) {
    int i = static_cast<int>(element.x) / kPixelStep;
    int j =static_cast<int>(element.y) / kPixelStep;

    double xi = static_cast<double>(i) / 100;
    double xj = static_cast<double>(j) / 100;

    double raw = perlin.GetValue(xi, xj, 0.0);
    double value = (raw + 1.0) / 2.0;

    int idx = (i) + ((j)*kWidth / kPixelStep);

    if (value < perlinThreshold / 1.5) {
      ressources_[idx] = Tile::kRock;
    } else if (value < perlinThreshold / 1.25) {
      ressources_[idx] = Tile::kTree;
    } else if (value < perlinThreshold) {
      ressources_[idx] = Tile::kFood;
    } else {
      ressources_[idx] = Tile::kEmpty;
    }
  }
}

void TileMap::Setup() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif  // TRACY_ENABLE

  textures.Load(files);

  Perlin();

  SetZone(sf::IntRect({0, 0}, sf::Vector2i(kWidth, kHeight)));
}

void TileMap::Reset() {
  for (auto &tile : buildings_) {
    tile = Tile::kEmpty;
  }

  Perlin();
}

void TileMap::Draw(sf::RenderWindow &window) {
  int tileIndex = 0;

  sf::Sprite sprite(textures.Get(Tile::kEmpty));

  sprite.setTextureRect(sf::IntRect({0, 0}, {kPixelStep, kPixelStep}));

  for (auto tile : tiles_) {
    if (!(tile == Tile::kEmpty)) {
      sprite.setPosition(ScreenPosition(tileIndex));
      sprite.setTexture(textures.Get(tile));
      window.draw(sprite);
    }
    tileIndex++;
  }

  tileIndex = 0;

  for (auto tile : ressources_) {
    if (!(tile == Tile::kEmpty)) {
      sprite.setPosition(ScreenPosition(tileIndex));
      sprite.setTexture(textures.Get(tile));
      window.draw(sprite);
    }
    tileIndex++;
  }

  tileIndex = 0;

  for (auto tile : buildings_) {
    if (!(tile == Tile::kEmpty)) {
      sprite.setPosition(ScreenPosition(tileIndex));
      sprite.setTexture(textures.Get(tile));
      window.draw(sprite);
    }
    tileIndex++;
  }
}

void TileMap::SetResourcesTile(int idx, Tile tile) {
  if (idx >= 0 && idx < ressources_.size()) {
    ressources_[idx] = tile;
  }
}

void TileMap::SetTile(int idx, Tile tile) {
  if (idx > 0 && idx < tiles_.size()) {
    tiles_[idx] = tile;
  }
}

std::vector<sf::Vector2f> TileMap::GetWalkables() const{
    return walkables_;
}

std::vector<int> TileMap::GetCollectibles(Tile search_tile){

  std::vector<int> collectibles;

  for (int tile_index = 0; tile_index < ressources_.size(); ++tile_index) {
    if (ressources_[tile_index] == search_tile) {
      collectibles.emplace_back(tile_index);
    }
  }

  return collectibles;

}

sf::Vector2f TileMap::ScreenPosition(const int index){
    float x = ceil((index % (kWidth / kPixelStep)) * kPixelStep);
    float y = ceil((index / (kWidth / kPixelStep)) * kPixelStep);

    //std::cout << "Calculated Screen Position : " << x << "." << y << "\n";

    return {x, y};
}

int TileMap::Index(const sf::Vector2f screenPosition){
    return static_cast<int>(ceil(screenPosition.y / kPixelStep * kWidth / kPixelStep)) +
           static_cast<int>(ceil(screenPosition.x / kPixelStep));
}

sf::Vector2f TileMap::TilePos(sf::Vector2i pos) {

  return {static_cast<float>(ceil(pos.x / kPixelStep) * kPixelStep),
          static_cast<float>(ceil(pos.y / kPixelStep) * kPixelStep)};

}


TileMap::Tile TileMap::GetBuilding(int index) const {
 return buildings_.at(index);
}

TileMap::Tile TileMap::GetGroundType(int index) { return tiles_.at(index); }

float TileMap::Distance(sf::Vector2f p1, sf::Vector2f p2) {
  float a,b;
  a = p1.x - p2.x;
  b = p1.y - p2.y;
  return sqrt(a * a + b * b);
}


void TileMap::AddBuilding(sf::Vector2f position, api::buildings::BuildingsType type){
  switch (type) {

    case api::buildings::BuildingsType::kMine:
      buildings_[Index(position)] = Tile::kMine;
      break;

    case api::buildings::BuildingsType::kLumber:
      buildings_[Index(position)] = Tile::kLumber;
      break;

    case api::buildings::BuildingsType::kWindmill:
      buildings_[Index(position)] = Tile::kWindmill;
      break;

    default:
      break;
  }
}

const sf::Texture& TileMap::GetBuildingTexture(api::buildings::BuildingsType type) {

  Tile t;
  switch (type) {
    case api::buildings::BuildingsType::kLumber:
      t = Tile::kLumber;
      break;
    case api::buildings::BuildingsType::kMine:
      t = Tile::kMine;
      break;
    case api::buildings::BuildingsType::kWindmill:
       t = Tile::kWindmill;
      break;
    case api::buildings::BuildingsType::kNone:
        t = Tile::kEmpty;
      break;
    default:
        t = Tile::kEmpty;
      break;
  }

  return textures.Get(t);
}
