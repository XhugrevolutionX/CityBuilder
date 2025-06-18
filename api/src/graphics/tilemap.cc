//
// Created by sebas on 15/05/2025.
//
#include "graphics/tilemap.h"

#include <noise/noise.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <random>

TileMap::TileMap(){
}

void TileMap::Setup(){
    textures.Load(files);

    noise::module::Perlin perlin;

    perlin.SetSeed(150);             // Set seed for reproducibility
    perlin.SetFrequency(5);        // Controls the "zoom" level
    perlin.SetPersistence(1);      // Amplitude of successive octaves
    perlin.SetLacunarity(1);       // Frequency multiplier between octaves
    perlin.SetOctaveCount(2);        // Number of octaves (layers of detail)
    perlin.SetNoiseQuality(noise::QUALITY_STD); // QUALITY_FAST, QUALITY_STD, or QUALITY_BEST

    for (int i = 0; i < kHeight/kPixelStep; i++) {
      for (int j = 0; j < kWidth/kPixelStep; j++) {

        double xi = static_cast<double>(j) / 100;
        double xj = static_cast<double>(i) / 100;

        double raw = perlin.GetValue(xi, xj, 0.0);
        double value = (raw + 1.0) / 2.0;

        int idx = (j) + ((i) * kWidth/kPixelStep);
        if (value < perlinThreshold) {
          tiles_[idx] = Tile::kGrass;

          walkables_.push_back(ScreenPosition(idx));
        }
        else {
          tiles_[idx] = Tile::kWater;
        }
      }
    }

     perlin.SetSeed(50);             // Set seed for reproducibility
     perlin.SetFrequency(5);        // Controls the "zoom" level
     perlin.SetPersistence(0.3);      // Amplitude of successive octaves
     perlin.SetLacunarity(2);       // Frequency multiplier between octaves
     perlin.SetOctaveCount(3);        // Number of octaves (layers of detail)
     perlin.SetNoiseQuality(noise::QUALITY_STD); // QUALITY_FAST, QUALITY_STD, or QUALITY_BEST


    for (auto element : walkables_) {

       int i = element.x / kPixelStep;
       int j = element.y / kPixelStep;

       double xi = static_cast<double>(j) / 100;
       double xj = static_cast<double>(i) / 100;

       double raw = perlin.GetValue(xi, xj, 0.0);
       double value = (raw + 1.0) / 2.0;

       int idx = (i) + ((j) * kWidth/kPixelStep);

       if (idx == 0 || idx == 10 || idx == 310 || idx == 300) {
         ressources_[idx] = Tile::kMaison;
       }
       else {
         if (value < perlinThreshold) {
           ressources_[idx] = Tile::kTree;
         }
         else {
           ressources_[idx] = Tile::kEmpty;
         }
       }
    }

}

void TileMap::Draw(sf::RenderWindow &window){
    int tileIndex = 0;

    sf::Sprite sprite(textures.Get(Tile::kEmpty));

    for (auto tile: tiles_) {
        sprite.setPosition(ScreenPosition(tileIndex));
        sprite.setTexture(textures.Get(tile));
        window.draw(sprite);

        tileIndex++;
    }

    tileIndex = 0;

    for (auto tile: ressources_) {
      if (!(tile == Tile::kEmpty)) {
          sprite.setPosition(ScreenPosition(tileIndex));
          sprite.setTexture(textures.Get(tile));
          window.draw(sprite);
      }
        tileIndex++;
    }
}

std::vector<sf::Vector2f> TileMap::GetWalkables() const{
    return walkables_;
}

sf::Vector2f TileMap::ScreenPosition(const int index){
    float x = ceil((index % (kWidth / kPixelStep)) * kPixelStep);
    float y = ceil((index / (kWidth / kPixelStep)) * kPixelStep);

    //std::cout << "Calculated Screen Position : " << x << "." << y << "\n";

    return {x, y};
}

int TileMap::Index(const sf::Vector2f screenPosition){
    return static_cast<int>(ceil(screenPosition.y / kPixelStep * kWidth)) +
           static_cast<int>(ceil(screenPosition.x / kPixelStep));
}

std::vector<sf::Vector2f> TileMap::GetHouses() const {
  std::vector<sf::Vector2f> houses;
  int tileIndex = 0;
  for (auto element : ressources_) {
    if (element == Tile::kMaison) {
      houses.emplace_back(ScreenPosition(tileIndex));
    }
    tileIndex++;
  }
  if (houses.empty()) {
    return std::vector<sf::Vector2f>();
  }
  return houses;
};
