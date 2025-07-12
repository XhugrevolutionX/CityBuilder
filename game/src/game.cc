#include "game.h"

#include "SFML/Graphics.hpp"
#include "ai/npc_manager.h"
#include "buildings/buildings_manager.h"
#include "graphics/tilemap.h"
#include "resources/stock_manager.h"
#include "ui/button_factory.h"
#include "ui/cursor_indicator.h"
#include "ui/ui_manager.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif  // TRACY_ENABLE

namespace game {
namespace {
sf::Clock clock_;

sf::RenderWindow window_;

auto tilemap_ptr_ = std::make_unique<TileMap>();

//Managers
api::ai::NpcManager npc_manager_;
api::buildings::BuildingsManager buildings_manager_;
ResourceManager resource_manager_;
api::resources::stock_manager stock_manager_;

api::ui::UiManager ui_manager_;

//Events
void ChopEvent(int index, float total_quantity, float quantity, api::resources::ResourcesType type) {
  // std::cout << "chop event : " << index << "," << quantity << "\n";
  if (quantity <= 0) {
    tilemap_ptr_->SetResourcesTile(index, TileMap::Tile::kEmpty);

    stock_manager_.AddStock(type, total_quantity);
  }
}

void GrowEvent(int index, api::resources::ResourcesType type) {
  switch (type) {
    case api::resources::ResourcesType::kWood:
      tilemap_ptr_->SetResourcesTile(index, TileMap::Tile::kTree);
      break;
    case api::resources::ResourcesType::kFood:
      tilemap_ptr_->SetResourcesTile(index, TileMap::Tile::kFood);
      break;
    case api::resources::ResourcesType::kStone:
      tilemap_ptr_->SetResourcesTile(index, TileMap::Tile::kRock);
      break;
    case api::resources::ResourcesType::kNone:
      tilemap_ptr_->SetResourcesTile(index, TileMap::Tile::kEmpty);
      break;
    default:
      tilemap_ptr_->SetResourcesTile(index, TileMap::Tile::kEmpty);
      break;
  }
}

void Setup() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif  // TRACY_ENABLE

  //Setup tilemap
  tilemap_ptr_->Setup();

  //Load the resources
  resource_manager_.LoadResources(api::resources::ResourcesType::kWood, tilemap_ptr_->GetCollectibles(TileMap::Tile::kTree), ChopEvent);
  resource_manager_.LoadResources(api::resources::ResourcesType::kFood, tilemap_ptr_->GetCollectibles(TileMap::Tile::kFood), ChopEvent);
  resource_manager_.LoadResources(api::resources::ResourcesType::kStone, tilemap_ptr_->GetCollectibles(TileMap::Tile::kRock), ChopEvent);


  // Create the main window
  {
#ifdef TRACY_ENABLE
    ZoneNamedN(create_window_event, "Window Creation", true);
#endif  // TRACY_ENABLE
    window_.create(sf::VideoMode({TileMap::GetSize()}), "SFML window");
  }

  //Setup prices for the buildings
  buildings_manager_.SetupPrices();

  //Setup Ui
  ui_manager_.Setup(window_, &buildings_manager_, tilemap_ptr_.get(), &resource_manager_, ChopEvent);

  //Attach click behavior to the tilemap
  tilemap_ptr_->OnReleasedLeft = []() {
    std::cout << "Clicked tilemap" << "\n";
    if (ui_manager_.building_adding_type_ != api::buildings::BuildingsType::kNone) {
      if (tilemap_ptr_->GetGroundType(TileMap::Index(TileMap::TilePos(sf::Mouse::getPosition(window_)))) == TileMap::Tile::kGrass) {
        if (buildings_manager_.GetPrice(ui_manager_.building_adding_type_).first <= stock_manager_.GetStock(api::resources::ResourcesType::kWood) && buildings_manager_.GetPrice(ui_manager_.building_adding_type_).second <= stock_manager_.GetStock(api::resources::ResourcesType::kStone)) {

          stock_manager_.RemoveStock(api::resources::ResourcesType::kWood, buildings_manager_.GetPrice(ui_manager_.building_adding_type_).first);
          stock_manager_.RemoveStock(api::resources::ResourcesType::kStone, buildings_manager_.GetPrice(ui_manager_.building_adding_type_).second);

          buildings_manager_.Add(ui_manager_.building_adding_type_, TileMap::TilePos(sf::Mouse::getPosition(window_)), &npc_manager_, tilemap_ptr_.get(), &resource_manager_, &stock_manager_);

          ui_manager_.building_adding_type_ = api::buildings::BuildingsType::kNone;
          ui_manager_.SetCursorTexture(tilemap_ptr_.get());
        } else {
          std::cout << "Not Enough Materials" << "\n";
        }
      }
      else {
        std::cout << "Cannot place buildings here" << "\n";
      }
    }
  };
}
}  // namespace

void Loop() {
  Setup();

  // Start the game loop
  while (window_.isOpen()) {
#ifdef TRACY_ENABLE
    ZoneNamedN(game_loop_event, "Game Loop", true);
#endif  // TRACY_ENABLE

    auto dt = clock_.restart().asSeconds();

    {
#ifdef TRACY_ENABLE
      ZoneNamedN(event_handling_event, "Event Handling", true);
#endif  // TRACY_ENABLE
        // Process events = Input frame
      while (const std::optional event = window_.pollEvent()) {
        // Close window: exit
        if (event->is<sf::Event::Closed>()) {
          window_.close();
        }

        bool buttonsWasClicked = false;

        ui_manager_.HandleEvents(event, buttonsWasClicked);
        tilemap_ptr_->HandleEvent(event, buttonsWasClicked);
      }
    }

    //cursor_indicator_.SetPosition(sf::Vector2f(sf::Mouse::getPosition(window_).x + 10.f, sf::Mouse::getPosition(window_).y + 10.f));
    ui_manager_.SetCursorPosition(window_);

    // GamePlay, physic frame
    npc_manager_.Update(dt);
    buildings_manager_.Update(dt);
    resource_manager_.Update(dt, GrowEvent);


    // Graphic frame
    window_.clear();

    tilemap_ptr_->Draw(window_);
    npc_manager_.Draw(window_);
    ui_manager_.Draw(window_, stock_manager_);

    {
      #ifdef TRACY_ENABLE
            ZoneNamedN(display_event, "Display Handling", true);
      #endif  // TRACY_ENABLE
      window_.display();
    }

    #ifdef TRACY_ENABLE
        FrameMark;
    #endif  // TRACY_ENABLE
  }
}
}  // namespace game
