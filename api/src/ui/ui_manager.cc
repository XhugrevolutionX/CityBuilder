//
// Created by hugze on 12.07.2025.
//

#include "ui/ui_manager.h"

namespace api::ui {

void UiManager::Setup(
    sf::RenderWindow& window, buildings::BuildingsManager* buildings_manager,
    TileMap* tilemap, ResourceManager* resource_manager,
    std::function<void(int, float, float, resources::ResourcesType)>
        ChopEvent) {
  if (!bg_ui_.loadFromFile("_assets/sprites/bg_ui.png")) {
    std::cerr << "Error loading texture bg_ui.png" << std::endl;
  }

  ui_button_background_.setTexture(&bg_ui_);
  ui_button_background_.setSize({(float)window.getSize().x, 120.f});
  ui_button_background_.setOrigin({ui_button_background_.getSize().x / 2,
                                   ui_button_background_.getSize().y / 2});
  ui_button_background_.setPosition(
      {(float)window.getSize().x / 2, (float)window.getSize().y - 60.f});

  ui_resources_background_.setTexture(&bg_ui_);
  ui_resources_background_.setSize({180.f, 120.f});
  ui_resources_background_.setOrigin(
      {ui_resources_background_.getSize().x / 2,
       ui_resources_background_.getSize().y / 2});
  ui_resources_background_.setPosition({90.f, 60.f});

  // Create the buttons and attach their click behaviors
  btn_lumber_ = btn_factory_.CreateLabelButton(
      sf::Vector2f(150.f, window.getSize().y - 75.f), "Lumber",
      "Wood: " +
          std::to_string(
              buildings_manager->GetPrice(buildings::BuildingsType::kLumber)
                  .first) +
          ", Stone: " +
          std::to_string(
              buildings_manager->GetPrice(buildings::BuildingsType::kLumber)
                  .second));
  btn_lumber_->OnReleasedLeft = [this, tilemap]() {
    building_adding_type_ = buildings::BuildingsType::kLumber;
    cursor_indicator_.SetTexture(
        tilemap->GetBuildingTexture(building_adding_type_));
  };

  btn_mine_ = btn_factory_.CreateLabelButton(
      sf::Vector2f(250.f, window.getSize().y - 75.f), "Mine",
      "Wood: " +
          std::to_string(
              buildings_manager->GetPrice(buildings::BuildingsType::kMine)
                  .first) +
          ", Stone: " +
          std::to_string(
              buildings_manager->GetPrice(buildings::BuildingsType::kMine)
                  .second));
  btn_mine_->OnReleasedLeft = [this, tilemap]() {
    building_adding_type_ = api::buildings::BuildingsType::kMine;
    cursor_indicator_.SetTexture(
        tilemap->GetBuildingTexture(building_adding_type_));
  };

  btn_windmill_ = btn_factory_.CreateLabelButton(
      sf::Vector2f(350.f, window.getSize().y - 75.f), "Windmill",
      "Wood: " +
          std::to_string(
              buildings_manager->GetPrice(buildings::BuildingsType::kWindmill)
                  .first) +
          ", Stone: " +
          std::to_string(
              buildings_manager->GetPrice(buildings::BuildingsType::kWindmill)
                  .second));
  btn_windmill_->OnReleasedLeft = [this, tilemap]() {
    building_adding_type_ = api::buildings::BuildingsType::kWindmill;
    cursor_indicator_.SetTexture(
        tilemap->GetBuildingTexture(building_adding_type_));
  };

  btn_cancel_ = btn_factory_.CreateButton(
      sf::Vector2f(450.f, window.getSize().y - 75.f), "Cancel");
  btn_cancel_->OnReleasedLeft = [this, tilemap]() {
    building_adding_type_ = api::buildings::BuildingsType::kNone;
    cursor_indicator_.SetTexture(
        tilemap->GetBuildingTexture(building_adding_type_));
  };

  // btn_clear_ = btn_factory_.CreateButton(
  //     sf::Vector2f(window.getSize().x - 350.f, window.getSize().y - 75.f),
  //     "Clear");
  // btn_clear_->OnReleasedLeft = [tilemap, resource_manager, ChopEvent]() {
  //   for (int i = 0; i < (tilemap->GetSize().x * tilemap->GetSize().y);
  //        i++) {
  //     tilemap->SetResourcesTile(i, TileMap::Tile::kEmpty);
  //   }
  //   resource_manager->LoadResources(api::resources::ResourcesType::kWood,
  //   tilemap->GetCollectibles(TileMap::Tile::kTree), ChopEvent);
  //   resource_manager->LoadResources(api::resources::ResourcesType::kFood,
  //   tilemap->GetCollectibles(TileMap::Tile::kFood), ChopEvent);
  //   resource_manager->LoadResources(api::resources::ResourcesType::kStone,
  //   tilemap->GetCollectibles(TileMap::Tile::kRock), ChopEvent);
  // };

  btn_ui_ = btn_factory_.CreateButton(
      sf::Vector2f(window.getSize().x - 250.f, window.getSize().y - 75.f),
      "Ui");
  btn_ui_->OnReleasedLeft = [this]() { ui_ = !ui_; };
}
void UiManager::HandleEvents(std::optional<sf::Event> evt, bool &wasClicked) {
  if (ui_) {
    btn_mine_->HandleEvent(evt, wasClicked);
    btn_lumber_->HandleEvent(evt, wasClicked);
    btn_windmill_->HandleEvent(evt, wasClicked);
    btn_cancel_->HandleEvent(evt, wasClicked);
    //btn_clear_->HandleEvent(evt, wasClicked);
  }

  btn_ui_->HandleEvent(evt, wasClicked);
}

void UiManager::SetCursorTexture(TileMap* tilemap) {
  cursor_indicator_.SetTexture(tilemap->GetBuildingTexture(building_adding_type_));
}

void UiManager::SetCursorPosition(sf::RenderWindow& window) {
  cursor_indicator_.SetPosition(sf::Vector2f(sf::Mouse::getPosition(window).x + 10.f, sf::Mouse::getPosition(window).y + 10.f));
}

void UiManager::Draw(sf::RenderWindow& window, resources::stock_manager& stock_manager) const {

  if (ui_) {
    window.draw(ui_button_background_);
    window.draw(ui_resources_background_);
    btn_mine_->Draw(window);
    btn_lumber_->Draw(window);
    btn_windmill_->Draw(window);

    if (building_adding_type_ != buildings::BuildingsType::kNone) {
      btn_cancel_->Draw(window);
    }

    //btn_clear_->Draw(window_);

    stock_manager.Draw(window);
  }

  btn_ui_->Draw(window);

  if (building_adding_type_ != buildings::BuildingsType::kNone) {
    cursor_indicator_.Draw(window);
  }
}
}  // namespace api::ui