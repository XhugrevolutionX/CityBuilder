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


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 49);

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
          if (dis(gen) == 0) {
            //replace 1 in 50 grass tiles with a house
            tiles_[idx] = Tile::kMaison;
          }
          else {
            tiles_[idx] = Tile::kGrass16;
          }
          walkables_.push_back(ScreenPosition(idx));
        }
        else {
          tiles_[idx] = Tile::kWater;
        }
      }
    }
}

void TileMap::Draw(sf::RenderWindow &window){
    int tileIndex = 0;

    sf::Sprite sprite(textures.Get(Tile::kEmpty));

    for (auto tile: tiles_) {
        sprite.setPosition(ScreenPosition(tileIndex));

        //puts grass underneath the houses
        if (tile == Tile::kMaison) {
          sprite.setTexture(textures.Get(Tile::kGrass16));
          window.draw(sprite);
        }
        sprite.setTexture(textures.Get(tile));
        window.draw(sprite);

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
