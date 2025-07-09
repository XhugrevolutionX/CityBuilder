#include "game.h"

#include "SFML/Graphics.hpp"
#include "ai/npc_manager.h"
#include "buildings/buildings_manager.h"
#include "graphics/tilemap.h"
#include "resources/StockManager.h"
#include "ui/button_factory.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif  // TRACY_ENABLE

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

api::ui::ButtonFactory btn_factory_;

ResourceManager resource_manager_;

api::resources::StockManager stock_manager_;

sf::Font font_;
sf::Text prices_text_(font_, "", 25);

bool ui_ = true;
bool prices_ = true;

void ChopEvent(int index, float total_quantity, float quantity, api::resources::ResourcesType type) {
  // std::cout << "chop event : " << index << "," << quantity << "\n";
  if (quantity <= 0) {
    tilemap_ptr_->SetResourcesTile(index, TileMap::Tile::kEmpty);

    stock_manager_.AddStock(type, total_quantity);
  }
}

void Setup() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif  // TRACY_ENBALE

  tilemap_ptr_->Setup();

  {
#ifdef TRACY_ENABLE
    ZoneNamedN(create_window_event, "Window Creation", true);
#endif  // TRACY_ENBALE
    // Create the main window
    window_.create(sf::VideoMode({tilemap_ptr_.get()->GetSize()}), "SFML window");
  }

  tilemap_ptr_->OnReleasedLeft = []() {
    std::cout << "Clicked tilemap" << "\n";
    if (building_adding_type != api::buildings::BuildingsType::kNone) {
      if (tilemap_ptr_->GetGroundType(TileMap::Index(TileMap::TilePos(sf::Mouse::getPosition(window_)))) == TileMap::Tile::kGrass) {
        if (buildings_manager_.GetPrice(building_adding_type).x <= stock_manager_.GetStock(api::resources::ResourcesType::kWood) && buildings_manager_.GetPrice(building_adding_type).y <= stock_manager_.GetStock(api::resources::ResourcesType::kStone)) {
          stock_manager_.RemoveStock(api::resources::ResourcesType::kWood, buildings_manager_.GetPrice(building_adding_type).x);
          stock_manager_.RemoveStock(api::resources::ResourcesType::kStone, buildings_manager_.GetPrice(building_adding_type).y);
          buildings_manager_.Add(building_adding_type, TileMap::TilePos(sf::Mouse::getPosition(window_)), &npc_manager_, tilemap_ptr_.get(), &resource_manager_, &stock_manager_);
        } else {
          std::cout << "Not Enough Materials" << "\n";
        }
      }
      else {
        std::cout << "Cannot place buildings here" << "\n";
      }

      building_adding_type = api::buildings::BuildingsType::kNone;
    }
  };

  if (!font_.openFromFile("_assets/fonts/BKANT.TTF")) {
    // handle error
  }
  prices_text_.setFont(font_);
  prices_text_.setFillColor(sf::Color::Black);


  btnLumber = btn_factory_.CreateButton(sf::Vector2f(100.f, window_.getSize().y - 100.f), "Lumber");
  btnLumber->OnReleasedLeft = []() {
    building_adding_type = api::buildings::BuildingsType::kLumber;
  };
  btnLumber->OnHoverEnter = []() { prices_ = true; prices_text_.setString("Wood: " + std::to_string(buildings_manager_.GetPrice(api::buildings::BuildingsType::kLumber).x) + ", Stone: " + std::to_string(buildings_manager_.GetPrice(api::buildings::BuildingsType::kLumber).y)); prices_text_.setPosition({100.f, window_.getSize().y - 150.f});};
  btnLumber->OnHoverExit = []() { prices_ = false;};

  btnMine = btn_factory_.CreateButton(sf::Vector2f(200.f, window_.getSize().y - 100.f), "Mine");
  btnMine->OnReleasedLeft = []() {
    building_adding_type = api::buildings::BuildingsType::kMine;
  };
  btnMine->OnHoverEnter = []() { prices_ = true; prices_text_.setString("Wood: " + std::to_string(buildings_manager_.GetPrice(api::buildings::BuildingsType::kMine).x) + ", Stone: " + std::to_string(buildings_manager_.GetPrice(api::buildings::BuildingsType::kMine).y)); prices_text_.setPosition({200.f, window_.getSize().y - 150.f});};
  btnMine->OnHoverExit = []() { prices_ = false;};

  btnWindmill = btn_factory_.CreateButton(sf::Vector2f(300.f, window_.getSize().y - 100.f), "Windmill");
  btnWindmill->OnReleasedLeft = []() {
    building_adding_type = api::buildings::BuildingsType::kWindmill;
  };
  btnWindmill->OnHoverEnter = []() { prices_ = true; prices_text_.setString("Wood: " + std::to_string(buildings_manager_.GetPrice(api::buildings::BuildingsType::kWindmill).x) + ", Stone: " + std::to_string(buildings_manager_.GetPrice(api::buildings::BuildingsType::kWindmill).y)); prices_text_.setPosition({300.f, window_.getSize().y - 150.f});};
  btnWindmill->OnHoverExit = []() { prices_ = false;};

  btnClear = btn_factory_.CreateButton(
      sf::Vector2f(400.f, window_.getSize().y - 100.f), "Clear");
  btnClear->OnReleasedLeft = []() {
    for (int i = 0; i < (tilemap_ptr_->GetSize().x * tilemap_ptr_->GetSize().y);
         i++) {
      tilemap_ptr_->SetResourcesTile(i, TileMap::Tile::kEmpty);
    }
    resource_manager_.LoadRessources(
        api::resources::ResourcesType::kWood,
        tilemap_ptr_->GetCollectibles(TileMap::Tile::kTree), ChopEvent);
    resource_manager_.LoadRessources(
        api::resources::ResourcesType::kFood,
        tilemap_ptr_->GetCollectibles(TileMap::Tile::kFood), ChopEvent);
    resource_manager_.LoadRessources(
        api::resources::ResourcesType::kStone,
        tilemap_ptr_->GetCollectibles(TileMap::Tile::kRock), ChopEvent);
  };

  btnUi = btn_factory_.CreateButton(sf::Vector2f(window_.getSize().x - 100.f, window_.getSize().y - 100.f), "Ui");
  btnUi->OnReleasedLeft = []() { ui_ = !ui_; };

  resource_manager_.LoadRessources(api::resources::ResourcesType::kWood, tilemap_ptr_->GetCollectibles(TileMap::Tile::kTree), ChopEvent);
  resource_manager_.LoadRessources(api::resources::ResourcesType::kFood, tilemap_ptr_->GetCollectibles(TileMap::Tile::kFood), ChopEvent);
  resource_manager_.LoadRessources(api::resources::ResourcesType::kStone, tilemap_ptr_->GetCollectibles(TileMap::Tile::kRock), ChopEvent);
}
}  // namespace

void Loop() {
  Setup();

  // Start the game loop
  while (window_.isOpen()) {
#ifdef TRACY_ENABLE
    ZoneNamedN(game_loop_event, "Game Loop", true);
#endif  // TRACY_ENABLE

    auto dt = clock.restart().asSeconds();

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
        btnMine->HandleEvent(event, buttonsWasClicked);
        btnLumber->HandleEvent(event, buttonsWasClicked);
        btnWindmill->HandleEvent(event, buttonsWasClicked);
        btnClear->HandleEvent(event, buttonsWasClicked);
        btnUi->HandleEvent(event, buttonsWasClicked);

        tilemap_ptr_->HandleEvent(event, buttonsWasClicked);
      }
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

    if (prices_) {
      window_.draw(prices_text_);
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
