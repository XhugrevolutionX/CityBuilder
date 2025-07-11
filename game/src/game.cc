#include "game.h"

#include "SFML/Graphics.hpp"
#include "ai/npc_manager.h"
#include "buildings/buildings_manager.h"
#include "graphics/tilemap.h"
#include "resources/StockManager.h"
#include "ui/button_factory.h"
#include "ui/cursor_indicator.h"
#include "ui/label_button.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif  // TRACY_ENABLE

namespace game {
namespace {
sf::Clock clock_;

sf::RenderWindow window_;

auto tilemap_ptr_ = std::make_unique<TileMap>();

api::ai::NpcManager npc_manager_;
api::buildings::BuildingsManager buildings_manager_;

std::unique_ptr<api::ui::LabelButton> btn_mine_;
std::unique_ptr<api::ui::LabelButton> btn_lumber_;
std::unique_ptr<api::ui::LabelButton> btn_windmill_;
std::unique_ptr<api::ui::Button> btn_cancel_;
//std::unique_ptr<api::ui::Button> btn_clear_;
std::unique_ptr<api::ui::Button> btn_ui_;

api::buildings::BuildingsType building_adding_type_ = api::buildings::BuildingsType::kNone;

api::ui::ButtonFactory btn_factory_;

ResourceManager resource_manager_;

api::resources::StockManager stock_manager_;

sf::RectangleShape ui_button_background_;
sf::RectangleShape ui_resources_background_;
sf::Texture bg_ui_;

api::ui::CursorIndicator cursor_indicator_;

bool ui_ = true;
bool prices_ = true;

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
#endif  // TRACY_ENBALE

  //Setup tilemap
  tilemap_ptr_->Setup();

  {
#ifdef TRACY_ENABLE
    ZoneNamedN(create_window_event, "Window Creation", true);
#endif  // TRACY_ENBALE
    // Create the main window
    window_.create(sf::VideoMode({tilemap_ptr_.get()->GetSize()}), "SFML window");
  }

  //Setup the prices for the buildings
  buildings_manager_.SetupPrices();

  // Attach click behavior to the tilemap
  tilemap_ptr_->OnReleasedLeft = []() {
    std::cout << "Clicked tilemap" << "\n";
    if (building_adding_type_ != api::buildings::BuildingsType::kNone) {
      if (tilemap_ptr_->GetGroundType(TileMap::Index(TileMap::TilePos(sf::Mouse::getPosition(window_)))) == TileMap::Tile::kGrass) {
        if (buildings_manager_.GetPrice(building_adding_type_).first <= stock_manager_.GetStock(api::resources::ResourcesType::kWood) && buildings_manager_.GetPrice(building_adding_type_).second <= stock_manager_.GetStock(api::resources::ResourcesType::kStone)) {

          stock_manager_.RemoveStock(api::resources::ResourcesType::kWood, buildings_manager_.GetPrice(building_adding_type_).first);
          stock_manager_.RemoveStock(api::resources::ResourcesType::kStone, buildings_manager_.GetPrice(building_adding_type_).second);

          buildings_manager_.Add(building_adding_type_, TileMap::TilePos(sf::Mouse::getPosition(window_)), &npc_manager_, tilemap_ptr_.get(), &resource_manager_, &stock_manager_);

          building_adding_type_ = api::buildings::BuildingsType::kNone;
          cursor_indicator_.SetTexture(tilemap_ptr_->GetBuildingTexture(building_adding_type_));
        } else {
          std::cout << "Not Enough Materials" << "\n";
        }
      }
      else {
        std::cout << "Cannot place buildings here" << "\n";
      }


    }
  };

  //Create the UI backgrounds
  if (!bg_ui_.loadFromFile("_assets/sprites/bg_ui.png")) {
    std::cerr << "Error loading texture bg_ui.png" << std::endl;
  }

  ui_button_background_.setTexture(&bg_ui_);
  ui_button_background_.setSize({ (float)window_.getSize().x, 120.f});
  ui_button_background_.setOrigin({ ui_button_background_.getSize().x / 2, ui_button_background_.getSize().y / 2});
  ui_button_background_.setPosition({(float)window_.getSize().x / 2, (float)window_.getSize().y - 60.f});

  ui_resources_background_.setTexture(&bg_ui_);
  ui_resources_background_.setSize({ 180.f, 120.f});
  ui_resources_background_.setOrigin({ ui_resources_background_.getSize().x / 2, ui_resources_background_.getSize().y / 2});
  ui_resources_background_.setPosition({90.f, 60.f});


  //Create the buttons and attach their click behaviors
  btn_lumber_ = btn_factory_.CreateLabelButton(sf::Vector2f(150.f, window_.getSize().y - 75.f), "Lumber", "Wood: " + std::to_string(buildings_manager_.GetPrice(api::buildings::BuildingsType::kLumber).first) + ", Stone: " + std::to_string(buildings_manager_.GetPrice(api::buildings::BuildingsType::kLumber).second));
  btn_lumber_->OnReleasedLeft = []() {
    building_adding_type_ = api::buildings::BuildingsType::kLumber;
    cursor_indicator_.SetTexture(tilemap_ptr_->GetBuildingTexture(building_adding_type_));
  };

  btn_mine_ = btn_factory_.CreateLabelButton(sf::Vector2f(250.f, window_.getSize().y - 75.f), "Mine", "Wood: " + std::to_string(buildings_manager_.GetPrice(api::buildings::BuildingsType::kMine).first) + ", Stone: " + std::to_string(buildings_manager_.GetPrice(api::buildings::BuildingsType::kMine).second));
  btn_mine_->OnReleasedLeft = []() {
    building_adding_type_ = api::buildings::BuildingsType::kMine;
    cursor_indicator_.SetTexture(tilemap_ptr_->GetBuildingTexture(building_adding_type_));
  };

  btn_windmill_ = btn_factory_.CreateLabelButton(sf::Vector2f(350.f, window_.getSize().y - 75.f), "Windmill", "Wood: " + std::to_string(buildings_manager_.GetPrice(api::buildings::BuildingsType::kWindmill).first) + ", Stone: " + std::to_string(buildings_manager_.GetPrice(api::buildings::BuildingsType::kWindmill).second));
  btn_windmill_->OnReleasedLeft = []() {
    building_adding_type_ = api::buildings::BuildingsType::kWindmill;
    cursor_indicator_.SetTexture(tilemap_ptr_->GetBuildingTexture(building_adding_type_));
  };

  btn_cancel_ = btn_factory_.CreateButton(
    sf::Vector2f(450.f, window_.getSize().y - 75.f), "Cancel");
  btn_cancel_->OnReleasedLeft = []() {
    building_adding_type_ = api::buildings::BuildingsType::kNone;
    cursor_indicator_.SetTexture(tilemap_ptr_->GetBuildingTexture(building_adding_type_));
  };

  // btn_clear_ = btn_factory_.CreateButton(
  //     sf::Vector2f(window_.getSize().x - 350.f, window_.getSize().y - 75.f), "Clear");
  // btn_clear_->OnReleasedLeft = []() {
  //   for (int i = 0; i < (tilemap_ptr_->GetSize().x * tilemap_ptr_->GetSize().y);
  //        i++) {
  //     tilemap_ptr_->SetResourcesTile(i, TileMap::Tile::kEmpty);
  //   }
  //   resource_manager_.LoadResources(api::resources::ResourcesType::kWood, tilemap_ptr_->GetCollectibles(TileMap::Tile::kTree), ChopEvent);
  //   resource_manager_.LoadResources(api::resources::ResourcesType::kFood, tilemap_ptr_->GetCollectibles(TileMap::Tile::kFood), ChopEvent);
  //   resource_manager_.LoadResources(api::resources::ResourcesType::kStone, tilemap_ptr_->GetCollectibles(TileMap::Tile::kRock), ChopEvent);
  // };
  

  btn_ui_ = btn_factory_.CreateButton(sf::Vector2f(window_.getSize().x - 250.f, window_.getSize().y - 75.f), "Ui");
  btn_ui_->OnReleasedLeft = []() { ui_ = !ui_; };


  //Load the resources
  resource_manager_.LoadResources(api::resources::ResourcesType::kWood, tilemap_ptr_->GetCollectibles(TileMap::Tile::kTree), ChopEvent);
  resource_manager_.LoadResources(api::resources::ResourcesType::kFood, tilemap_ptr_->GetCollectibles(TileMap::Tile::kFood), ChopEvent);
  resource_manager_.LoadResources(api::resources::ResourcesType::kStone, tilemap_ptr_->GetCollectibles(TileMap::Tile::kRock), ChopEvent);

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
        if (ui_) {
          btn_mine_->HandleEvent(event, buttonsWasClicked);
          btn_lumber_->HandleEvent(event, buttonsWasClicked);
          btn_windmill_->HandleEvent(event, buttonsWasClicked);
          btn_cancel_->HandleEvent(event, buttonsWasClicked);
          //btn_clear_->HandleEvent(event, buttonsWasClicked);
        }

        btn_ui_->HandleEvent(event, buttonsWasClicked);

        tilemap_ptr_->HandleEvent(event, buttonsWasClicked);
      }
    }

    cursor_indicator_.SetPosition(sf::Vector2f(sf::Mouse::getPosition(window_).x + 10.f, sf::Mouse::getPosition(window_).y + 10.f));

    // GamePlay, physic frame
    npc_manager_.Update(dt);
    buildings_manager_.Update(dt);
    resource_manager_.Update(dt, GrowEvent);

    // Graphic frame
    window_.clear();

    tilemap_ptr_->Draw(window_);
    npc_manager_.Draw(window_);

    if (ui_) {
      window_.draw(ui_button_background_);
      window_.draw(ui_resources_background_);
      btn_mine_->Draw(window_);
      btn_lumber_->Draw(window_);
      btn_windmill_->Draw(window_);

      if (building_adding_type_ != api::buildings::BuildingsType::kNone) {
        btn_cancel_->Draw(window_);
      }

      //btn_clear_->Draw(window_);

      stock_manager_.Draw(window_);
    }

    btn_ui_->Draw(window_);

    if (building_adding_type_ != api::buildings::BuildingsType::kNone) {
      cursor_indicator_.Draw(window_);
    }

    {
      #ifdef TRACY_ENABLE
            ZoneNamedN(display_event, "Display Handling", true);
      #endif  // TRACY_ENBALE
      window_.display();
    }

    #ifdef TRACY_ENABLE
        FrameMark;
    #endif  // TRACY_ENABLE
  }
}
}  // namespace game
