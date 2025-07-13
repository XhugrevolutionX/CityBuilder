//
// Created by hugze on 12.07.2025.
//

#include "ui/ui_manager.h"

#include "ui/fading_message.h"

namespace api::ui {

void UiManager::Setup(sf::RenderWindow& window, buildings::BuildingsManager* buildings_manager, resources::StockManager* stock_manager, TileMap* tilemap, ResourceManager* resource_manager, std::function<void(int, float, float, resources::ResourcesType)>ChopEvent) {
  if (!bg_stocks_.loadFromFile("_assets/sprites/bg_stocks.png")) {
    std::cerr << "Error loading texture bg_stocks.png" << std::endl;
  }
  if (!bg_buttons_.loadFromFile("_assets/sprites/bg_buttons.png")) {
    std::cerr << "Error loading texture bg_buttons.png" << std::endl;
  }
  if (!bg_dev_buttons_.loadFromFile("_assets/sprites/bg_dev_buttons.png")) {
    std::cerr << "Error loading texture bg_dev_buttons.png" << std::endl;
  }

  if (!font_.openFromFile("_assets/fonts/ANTQUAB.TTF")) {
    std::cout << "Failed to load font" << std::endl;
  }

  // Create the backgrounds
  ui_button_background_.setTexture(&bg_buttons_);
  ui_button_background_.setSize({static_cast<float>(window.getSize().x), 120.f});
  ui_button_background_.setOrigin({ui_button_background_.getSize().x / 2, ui_button_background_.getSize().y / 2});
  ui_button_background_.setPosition({static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) - 60.f});

  ui_dev_button_background_.setTexture(&bg_dev_buttons_);
  ui_dev_button_background_.setSize({128.f, static_cast<float>(window.getSize().y) * .50f});
  ui_dev_button_background_.setOrigin({ui_dev_button_background_.getSize().x / 2, ui_dev_button_background_.getSize().y / 2});
  ui_dev_button_background_.setPosition({static_cast<float>(window.getSize().x - 80), static_cast<float>(window.getSize().y) * .25f});

  ui_resources_background_.setTexture(&bg_stocks_);
  ui_resources_background_.setSize({180.f, 120.f});
  ui_resources_background_.setOrigin({ui_resources_background_.getSize().x / 2, ui_resources_background_.getSize().y / 2});
  ui_resources_background_.setPosition({90.f, 60.f});

  // Create the gameplay buttons and attach their click behaviors
  btn_lumber_ = btn_factory_.CreateLabelButton(sf::Vector2f(150.f, static_cast<float>(window.getSize().y - 75)), "Lumber","Wood: " + std::to_string(buildings_manager->GetPrice(buildings::BuildingsType::kLumber).first) +", Stone: " +std::to_string(buildings_manager->GetPrice(buildings::BuildingsType::kLumber).second));
  btn_lumber_->OnReleasedLeft = [this, tilemap]()
  {
    building_adding_type_ = buildings::BuildingsType::kLumber;
    cursor_indicator_.SetTexture(tilemap->GetBuildingTexture(building_adding_type_));
  };

  btn_mine_ = btn_factory_.CreateLabelButton(sf::Vector2f(250.f, static_cast<float>(window.getSize().y) - 75), "Mine","Wood: " +std::to_string(buildings_manager->GetPrice(buildings::BuildingsType::kMine).first) +", Stone: " +std::to_string(buildings_manager->GetPrice(buildings::BuildingsType::kMine).second));
  btn_mine_->OnReleasedLeft = [this, tilemap]()
  {
    building_adding_type_ = api::buildings::BuildingsType::kMine;
    cursor_indicator_.SetTexture(tilemap->GetBuildingTexture(building_adding_type_));
  };

  btn_windmill_ = btn_factory_.CreateLabelButton(sf::Vector2f(350.f, static_cast<float>(window.getSize().y - 75)), "Windmill","Wood: " +std::to_string(buildings_manager->GetPrice(buildings::BuildingsType::kWindmill).first) +", Stone: " +std::to_string(buildings_manager->GetPrice(buildings::BuildingsType::kWindmill).second));
  btn_windmill_->OnReleasedLeft = [this, tilemap]()
  {
    building_adding_type_ = api::buildings::BuildingsType::kWindmill;
    cursor_indicator_.SetTexture(tilemap->GetBuildingTexture(building_adding_type_));
  };

  btn_cancel_ = btn_factory_.CreateButton(sf::Vector2f(450.f, static_cast<float>(window.getSize().y - 75)), "Cancel");
  btn_cancel_->OnReleasedLeft = [this, tilemap]()
  {
    building_adding_type_ = api::buildings::BuildingsType::kNone;
    cursor_indicator_.SetTexture(tilemap->GetBuildingTexture(building_adding_type_));
  };

  btn_ui_ = btn_factory_.CreateButton(sf::Vector2f(static_cast<float>(window.getSize().x - 250), static_cast<float>(window.getSize().y - 75)),"Ui");
  btn_ui_->OnReleasedLeft = [this]() { ui_ = !ui_; };

  // Create the dev buttons and attach their click behaviors

  btn_dev_ui_ = btn_factory_.CreateButton(sf::Vector2f(window.getSize().x - 350.f, window.getSize().y - 75.f),"Dev");
  btn_dev_ui_->OnReleasedLeft = [this]() {dev_ui_ = !dev_ui_;};

  btn_give_wood = btn_factory_.CreateButton(sf::Vector2f(window.getSize().x - 125.f, 25.f),"add wood");
  btn_give_wood->OnReleasedLeft = [this, stock_manager]() {stock_manager->AddStock(resources::ResourcesType::kWood, give_amount);};

  btn_give_stone = btn_factory_.CreateButton(sf::Vector2f(window.getSize().x - 125.f, 75.f),"add stone");
  btn_give_stone->OnReleasedLeft = [this, stock_manager]() {stock_manager->AddStock(resources::ResourcesType::kStone, give_amount);};

  btn_give_food = btn_factory_.CreateButton(sf::Vector2f(window.getSize().x - 125.f, 125.f),"add food");
  btn_give_food->OnReleasedLeft = [this, stock_manager]() {stock_manager->AddStock(resources::ResourcesType::kFood, give_amount);};

  btn_add_give_amount = btn_factory_.CreateButton(sf::Vector2f(window.getSize().x - 125.f, 225.f),"give +10");
  btn_add_give_amount->OnReleasedLeft = [this]() {give_amount += 10;};

  btn_sub_give_amount = btn_factory_.CreateButton(sf::Vector2f(window.getSize().x - 125.f, 275.f),"give -10");
  btn_sub_give_amount->OnReleasedLeft = [this]() {if (give_amount > 10) give_amount -= 10; else give_amount = 10;};

  btn_clear_ = btn_factory_.CreateButton(sf::Vector2f(window.getSize().x - 125.f, 375.f),"Clear");
  btn_clear_->OnReleasedLeft = [tilemap, resource_manager, ChopEvent]() {
    for (int i = 0; i < (tilemap->GetSize().x * tilemap->GetSize().y);
         i++) {
      tilemap->SetResourcesTile(i, TileMap::Tile::kEmpty);
    }
    resource_manager->LoadResources(api::resources::ResourcesType::kWood, tilemap->GetCollectibles(TileMap::Tile::kTree), ChopEvent);
    resource_manager->LoadResources(api::resources::ResourcesType::kFood, tilemap->GetCollectibles(TileMap::Tile::kFood), ChopEvent);
    resource_manager->LoadResources(api::resources::ResourcesType::kStone, tilemap->GetCollectibles(TileMap::Tile::kRock), ChopEvent);
  };

  //Give Amount Text
  give_amount_text_.setFont(font_);
  give_amount_text_.setString("Give Amount: " + std::to_string(give_amount));
  give_amount_text_.setCharacterSize(12);
  give_amount_text_.setFillColor(sf::Color::Black);
  give_amount_text_.setPosition(sf::Vector2f(window.getSize().x - 125.f, 175.f));

}
void UiManager::HandleEvents(std::optional<sf::Event> evt, bool &wasClicked) {
  if (ui_) {
    btn_mine_->HandleEvent(evt, wasClicked);
    btn_lumber_->HandleEvent(evt, wasClicked);
    btn_windmill_->HandleEvent(evt, wasClicked);
    btn_cancel_->HandleEvent(evt, wasClicked);
    btn_dev_ui_->HandleEvent(evt, wasClicked);

    if (dev_ui_) {
      btn_give_wood->HandleEvent(evt, wasClicked);
      btn_give_stone->HandleEvent(evt, wasClicked);
      btn_give_food->HandleEvent(evt, wasClicked);
      btn_add_give_amount->HandleEvent(evt, wasClicked);
      btn_sub_give_amount->HandleEvent(evt, wasClicked);
      btn_clear_->HandleEvent(evt, wasClicked);
    }
  }

  btn_ui_->HandleEvent(evt, wasClicked);
}

void UiManager::SetCursorTexture(TileMap* tilemap) {
  cursor_indicator_.SetTexture(tilemap->GetBuildingTexture(building_adding_type_));
}

void UiManager::Update(float dt, sf::RenderWindow& window) {

  for (auto& fading_message : fading_messages_) {
    fading_message.Update(dt);

    auto it = std::remove_if(fading_messages_.begin(), fading_messages_.end(), [](const FadingMessage& fading_message){return fading_message.Visible() == false;});
    fading_messages_.erase(it, fading_messages_.end());
  }

  cursor_indicator_.SetPosition(sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(window).x + 10),static_cast<float>(sf::Mouse::getPosition(window).y + 10)));

  give_amount_text_.setString("Give Amount: " + std::to_string(give_amount));
}
void UiManager::CreateFadingMessage(const std::string& text, sf::Vector2f pos, sf::Color color) {
  fading_messages_.emplace_back(font_, text, pos, color);
}

void UiManager::Draw(sf::RenderWindow& window, resources::StockManager& stock_manager) const {

  if (ui_) {

    for (auto& fading_message : fading_messages_) {
      fading_message.Draw(window);
    }

    window.draw(ui_button_background_);
    window.draw(ui_resources_background_);
    btn_mine_->Draw(window);
    btn_lumber_->Draw(window);
    btn_windmill_->Draw(window);

    if (building_adding_type_ != buildings::BuildingsType::kNone) {
      btn_cancel_->Draw(window);
    }

    stock_manager.Draw(window);

    if (dev_ui_) {
      window.draw(ui_dev_button_background_);
      btn_give_wood->Draw(window);
      btn_give_stone->Draw(window);
      btn_give_food->Draw(window);
      window.draw(give_amount_text_);
      btn_add_give_amount->Draw(window);
      btn_sub_give_amount->Draw(window);
      btn_clear_->Draw(window);
    }

    btn_dev_ui_->Draw(window);

  }

  btn_ui_->Draw(window);

  if (building_adding_type_ != buildings::BuildingsType::kNone) {
    cursor_indicator_.Draw(window);
  }
}
}  // namespace api::ui