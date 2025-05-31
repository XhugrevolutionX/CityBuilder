#include <SFML/Graphics/RenderWindow.hpp>
#include "../../api/include/resource_manager.h"
#include "tilemap.h"

namespace Game
{
    namespace
    {
        sf::RenderWindow window;
        Tilemap tilemap;

        void CreateTilemap()
        {
            tilemap.Setup(sf::Vector2u(window.getSize().x / tilemap.SpritSize().x, window.getSize().y / tilemap.SpritSize().y));

            tilemap.SetTiles();
        }

        void Setup()
        {
            window.create(sf::VideoMode({1600, 800}), "CityBuilder");
            ResourceManager::Setup();
            CreateTilemap();
        }
    } // namespace

    void Loop()
    {
        Setup();
        while(window.isOpen())
        {
            while(const std::optional event = window.pollEvent())
            {
                if(event->is<sf::Event::Closed>())
                {
                    window.close();
                }
            }

            window.clear();
            window.draw(tilemap);
            window.display();
        }
    }
} // namespace game
