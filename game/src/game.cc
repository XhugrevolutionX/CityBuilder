#include "game.h"

#include "SFML/Graphics.hpp"
#include "ai/npc_manager.h"
#include "buildings/buildings_manager.h"
#include "graphics/tilemap.h"
#include "resources/StockManager.h"
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
        std::unique_ptr<api::ui::Button> btnClear;
        std::unique_ptr<api::ui::Button> btnUi;

        api::buildings::BuildingsType building_adding_type = api::buildings::BuildingsType::kNone;

        api::ui::ButtonFactory btn_factory;

        ResourceManager resource_manager_;

        api::resources::StockManager stock_manager_;

        bool ui_ = true;

        void ChopEvent(int index, float total_quantity, float quantity, api::resources::ResourcesType type) {
          //std::cout << "chop event : " << index << "," << quantity << "\n";
          if (quantity <= 0){
            tilemap_ptr_->SetResourcesTile(index, TileMap::Tile::kEmpty);

            stock_manager_.AddStock(type, total_quantity);
            }
          }

        void Setup(){
          tilemap_ptr_->Setup();

          // Create the main window
          window_.create(sf::VideoMode({tilemap_ptr_.get()->GetSize()}), "SFML window");

          tilemap_ptr_->OnReleasedLeft = []() {
            std::cout << "Clicked tilemap" << "\n";
            buildings_manager_.Add(building_adding_type, TileMap::TilePos(sf::Mouse::getPosition(window_)), &npc_manager_, tilemap_ptr_.get(), &resource_manager_);
            building_adding_type = api::buildings::BuildingsType::kNone;
          };

          btnMine = btn_factory.CreateButton(sf::Vector2f(100.f, window_.getSize().y - 100.f), "Mine");
          btnMine->OnReleasedLeft = []() { building_adding_type = api::buildings::BuildingsType::kMine; };

          btnLumber = btn_factory.CreateButton(sf::Vector2f(200.f, window_.getSize().y - 100.f), "Lumber");
          btnLumber->OnReleasedLeft = []() { building_adding_type = api::buildings::BuildingsType::kLumber; };

          btnWindmill = btn_factory.CreateButton(sf::Vector2f(300.f, window_.getSize().y - 100.f), "Windmill");
          btnWindmill->OnReleasedLeft = []() {building_adding_type = api::buildings::BuildingsType::kWindmill; };

          btnClear = btn_factory.CreateButton(sf::Vector2f(400.f, window_.getSize().y - 100.f), "Clear");
          btnClear->OnReleasedLeft = []() {
            for (int i = 0; i < (tilemap_ptr_->GetSize().x * tilemap_ptr_->GetSize().y); i++) {
              tilemap_ptr_->SetResourcesTile(i, TileMap::Tile::kEmpty);
            }
            resource_manager_.LoadRessources(api::resources::ResourcesType::kWood,tilemap_ptr_->GetCollectibles(TileMap::Tile::kTree), ChopEvent);
            resource_manager_.LoadRessources(api::resources::ResourcesType::kFood, tilemap_ptr_->GetCollectibles(TileMap::Tile::kFood), ChopEvent);
            resource_manager_.LoadRessources(api::resources::ResourcesType::kStone,tilemap_ptr_->GetCollectibles(TileMap::Tile::kRock), ChopEvent);
          };


          btnUi = btn_factory.CreateButton(sf::Vector2f(window_.getSize().x - 100.f, window_.getSize().y - 100.f), "Ui");
          btnUi->OnReleasedLeft = []() { ui_ = !ui_; };

          resource_manager_.LoadRessources(api::resources::ResourcesType::kWood,tilemap_ptr_->GetCollectibles(TileMap::Tile::kTree), ChopEvent);
          resource_manager_.LoadRessources(api::resources::ResourcesType::kFood, tilemap_ptr_->GetCollectibles(TileMap::Tile::kFood), ChopEvent);
          resource_manager_.LoadRessources(api::resources::ResourcesType::kStone,tilemap_ptr_->GetCollectibles(TileMap::Tile::kRock), ChopEvent);

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
              btnClear->HandleEvent(event, buttonsWasClicked);
              btnUi->HandleEvent(event, buttonsWasClicked);

              tilemap_ptr_->HandleEvent(event, buttonsWasClicked);
            }

            // GamePlay, physic frame
            npc_manager_.Update(dt);
            buildings_manager_.Update(dt);

            // Graphic frame
            window_.clear();

            tilemap_ptr_->Draw(window_);
            npc_manager_.Draw(window_);

          if (ui_) {
            btnMine->Draw(window_);
            btnLumber->Draw(window_);
            btnWindmill->Draw(window_);
            btnClear->Draw(window_);

            stock_manager_.Draw(window_);
          }
            btnUi->Draw(window_);

            window_.display();
        }
    }
}
