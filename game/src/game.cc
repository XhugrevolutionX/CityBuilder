#include "game.h"

#include "SFML/Graphics.hpp"
#include "ai/npc_manager.h"
#include "buildings/buildings_manager.h"
#include "graphics/tilemap.h"
#include "ui/button_factory.h"

namespace game {
    namespace {
        sf::Clock clock;

        sf::RenderWindow window_;

        auto tilemap_ptr_ = std::make_unique<TileMap>();

        api::ai::NpcManager npc_manager_;
        api::buildings::BuildingsManager buildings_manager_;

        std::unique_ptr<api::ui::Button> btnMine;
        std::unique_ptr<api::ui::Button> btnLumber;
        std::unique_ptr<api::ui::Button> btnWindmill;

        api::buildings::BuildingsType building_adding_type = api::buildings::BuildingsType::kNone;

        api::ui::ButtonFactory btn_factory;

        RessourceManager ressource_manager_;

        void ChopEvent(int index, float quantity) {
          std::cout << "chop event : " << index << "," << quantity << "\n";
          if (quantity <= 0){
            tilemap_ptr_->SetTile(index, TileMap::Tile::kEmpty);
          }
        }

        void Setup(){
          // Create the main window
          window_.create(sf::VideoMode({1280, 1080}), "SFML window");

          tilemap_ptr_->Setup();
          tilemap_ptr_->OnReleasedLeft = []() {
            std::cout << "Clicked tilemap" << "\n";
            buildings_manager_.Add(building_adding_type,
                             TileMap::TilePos(sf::Mouse::getPosition(window_)),
                             tilemap_ptr_.get());
            building_adding_type = api::buildings::BuildingsType::kNone;
          };

          btnMine = btn_factory.CreateButton(sf::Vector2f(100.f, window_.getSize().y - 100.f), "Mine");
          btnMine->OnReleasedLeft = []() { building_adding_type = api::buildings::BuildingsType::kMine; };

          btnLumber = btn_factory.CreateButton(sf::Vector2f(200.f, window_.getSize().y - 100.f), "Lumber");
          btnLumber->OnReleasedLeft = []() { building_adding_type = api::buildings::BuildingsType::kLumber; };

          btnWindmill = btn_factory.CreateButton(sf::Vector2f(300.f, window_.getSize().y - 100.f), "Windmill");
          btnWindmill->OnReleasedLeft = []() {building_adding_type = api::buildings::BuildingsType::kWindmill; };

          ressource_manager_.LoadRessources(Ressource::Type::kWood,tilemap_ptr_->GetCollectibles(TileMap::Tile::kTree), ChopEvent);

          // ressource_manager_.LoadRessources(
          //         Ressource::Type::kFood,
          //         tilemap_ptr_->GetCollectibles(TileMap::Tile::kFood), ChopEvent);

          ressource_manager_.LoadRessources(Ressource::Type::kStone,tilemap_ptr_->GetCollectibles(TileMap::Tile::kRock), ChopEvent);

          npc_manager_.Add(api::ai::NpcType::kCyan, {0,0}, tilemap_ptr_.get(), ressource_manager_);
          //npc_manager_.Add(api::ai::NpcType::kRed, {0,0}, tilemap_ptr_.get(), ressource_manager_);


        }
    }

    void Loop(){
        Setup();

        // Start the game loop
        while (window_.isOpen()) {

            auto dt = clock.restart().asSeconds();

            // Process events = Input frame
            while (const std::optional event = window_.pollEvent()) {
                // Close window: exit
                if (event->is<sf::Event::Closed>()) {
                    window_.close();
                }

              bool buttonsWasClicked = false;
              btnMine->HandleEvent(event, buttonsWasClicked);
              btnLumber->HandleEvent(event, buttonsWasClicked);
              btnWindmill->HandleEvent(event, buttonsWasClicked);

              tilemap_ptr_->HandleEvent(event, buttonsWasClicked);
            }

            // GamePlay, physic frame
            npc_manager_.Update(dt);
            //buildings_manager_.Update(dt);

            // Graphic frame
            window_.clear();

            tilemap_ptr_->Draw(window_);
            npc_manager_.Draw(window_);

            btnMine->Draw(window_);
            btnLumber->Draw(window_);
            btnWindmill->Draw(window_);

            window_.display();
        }
    }
}
