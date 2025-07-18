//
// Created by hugze on 12.07.2025.
//

#include "ui/ui_manager.h"

#include "../../../game/include/game.h"
#include "ui/fading_message.h"

namespace api::ui {

void UiManager::Setup(sf::RenderWindow& window, buildings::BuildingsManager* buildings_manager, resources::StockManager* stock_manager, TileMap* tilemap, ResourceManager* resource_manager, ai::NpcManager* npc_manager, std::function<void(int, float, float, resources::ResourcesType)>ChopEvent) {
  //Load the assets
  if (!font_.openFromFile("_assets/fonts/ANTQUAB.TTF")) {
    std::cerr << "Failed to load font" << std::endl;
  }

  textures_.Load(files_);

  // Create the ui backgrounds
  ui_button_background_.setTexture(&textures_.Get(UiTextures::kBgButtons));
  ui_button_background_.setSize({static_cast<float>(window.getSize().x), 120.f});
  ui_button_background_.setOrigin({ui_button_background_.getSize().x / 2, ui_button_background_.getSize().y / 2});
  ui_button_background_.setPosition({static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) - 60.f});

  ui_dev_button_background_.setTexture(&textures_.Get(UiTextures::kBgDevButtons));
  ui_dev_button_background_.setSize({128.f, static_cast<float>(window.getSize().y) * .6f});
  ui_dev_button_background_.setOrigin({ui_dev_button_background_.getSize().x / 2, ui_dev_button_background_.getSize().y / 2});
  ui_dev_button_background_.setPosition({static_cast<float>(window.getSize().x - 80), static_cast<float>(window.getSize().y) * .3f});

  ui_resources_background_.setTexture(&textures_.Get(UiTextures::kBgStock));
  ui_resources_background_.setSize({180.f, 120.f});
  ui_resources_background_.setOrigin({ui_resources_background_.getSize().x / 2, ui_resources_background_.getSize().y / 2});
  ui_resources_background_.setPosition({90.f, 60.f});

  ui_game_over_background_.setTexture(&textures_.Get(UiTextures::kBgStock));
  ui_game_over_background_.setSize({static_cast<float>(window.getSize().x) / 4, static_cast<float>(window.getSize().y) / 4});
  ui_game_over_background_.setOrigin({ui_game_over_background_.getSize().x / 2, ui_game_over_background_.getSize().y / 2});
  ui_game_over_background_.setPosition({800.f, 450.f});

  // Create the gameplay buttons
  btn_lumber_ = btn_factory_.CreateLabelButton(sf::Vector2f(150.f, static_cast<float>(window.getSize().y - 75)), "Lumber","Wood: " + std::to_string(buildings_manager->GetPrice(buildings::BuildingsType::kLumber).first) +", Stone: " +std::to_string(buildings_manager->GetPrice(buildings::BuildingsType::kLumber).second));
  btn_lumber_->OnReleasedLeft = [this, tilemap]()
  {
    building_adding_type_ = buildings::BuildingsType::kLumber;
    cursor_indicator_.SetTexture(tilemap->GetBuildingTexture(building_adding_type_));
  };

  btn_mine_ = btn_factory_.CreateLabelButton(sf::Vector2f(250.f, static_cast<float>(window.getSize().y) - 75), "Mine","Wood: " + std::to_string(buildings_manager->GetPrice(buildings::BuildingsType::kMine).first) +", Stone: " +std::to_string(buildings_manager->GetPrice(buildings::BuildingsType::kMine).second));
  btn_mine_->OnReleasedLeft = [this, tilemap]()
  {
    building_adding_type_ = api::buildings::BuildingsType::kMine;
    cursor_indicator_.SetTexture(tilemap->GetBuildingTexture(building_adding_type_));
  };

  btn_windmill_ = btn_factory_.CreateLabelButton(sf::Vector2f(350.f, static_cast<float>(window.getSize().y - 75)), "Windmill","Wood: " + std::to_string(buildings_manager->GetPrice(buildings::BuildingsType::kWindmill).first) +", Stone: " +std::to_string(buildings_manager->GetPrice(buildings::BuildingsType::kWindmill).second));
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

  // Create the dev buttons
  btn_dev_ui_ = btn_factory_.CreateButton(sf::Vector2f(static_cast<float>(window.getSize().x) - 350.f, static_cast<float>(window.getSize().y) - 75.f),"Dev");
  btn_dev_ui_->OnReleasedLeft = [this]() {dev_ui_ = !dev_ui_;};

  btn_give_wood_ = btn_factory_.CreateButton(sf::Vector2f(static_cast<float>(window.getSize().x) - 125.f, 75.f),"Wood");
  btn_give_wood_->OnReleasedLeft = [this, stock_manager]() {stock_manager->AddStock(resources::ResourcesType::kWood, give_amount_);};

  btn_give_stone_ = btn_factory_.CreateButton(sf::Vector2f(static_cast<float>(window.getSize().x) - 125.f, 125.f),"Stone");
  btn_give_stone_->OnReleasedLeft = [this, stock_manager]() {stock_manager->AddStock(resources::ResourcesType::kStone, give_amount_);};

  btn_give_food_ = btn_factory_.CreateButton(sf::Vector2f(static_cast<float>(window.getSize().x) - 125.f, 175.f),"Food");
  btn_give_food_->OnReleasedLeft = [this, stock_manager]() {stock_manager->AddStock(resources::ResourcesType::kFood, give_amount_);};

  btn_add_give_amount_ = btn_factory_.CreateButton(sf::Vector2f(static_cast<float>(window.getSize().x) - 125.f, 275.f),"give +10");
  btn_add_give_amount_->OnReleasedLeft = [this]() {give_amount_ += 10;};

  btn_sub_give_amount_ = btn_factory_.CreateButton(sf::Vector2f(static_cast<float>(window.getSize().x) - 125.f, 325.f),"give -10");
  btn_sub_give_amount_->OnReleasedLeft = [this]() {give_amount_ -= 10;};

  btn_clear_ = btn_factory_.CreateButton(sf::Vector2f(static_cast<float>(window.getSize().x) - 125.f, 425.f),"Clear");
  btn_clear_->OnReleasedLeft = [tilemap, resource_manager, ChopEvent]() {
    for (int i = 0; i < (TileMap::GetSize().x * TileMap::GetSize().y);
         i++) {
      tilemap->SetResourcesTile(i, TileMap::Tile::kEmpty);
    }
    resource_manager->LoadResources(resources::ResourcesType::kWood, tilemap->GetCollectibles(TileMap::Tile::kTree), ChopEvent);
    resource_manager->LoadResources(resources::ResourcesType::kFood, tilemap->GetCollectibles(TileMap::Tile::kFood), ChopEvent);
    resource_manager->LoadResources(resources::ResourcesType::kStone, tilemap->GetCollectibles(TileMap::Tile::kRock), ChopEvent);
  };

  btn_kill_all_npc_ = btn_factory_.CreateButton(sf::Vector2f(static_cast<float>(window.getSize().x) - 125.f, 475.f),"Kill All");
  btn_kill_all_npc_->OnReleasedLeft = [npc_manager]() {npc_manager->KillAll();};


  //Create the Game Over Buttons
  btn_restart_ = btn_factory_.CreateButton(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.f - 125.f, static_cast<float>(window.getSize().y) / 2.f + 25.f),"Restart");
  btn_restart_->OnReleasedLeft = []() {game::Restart();};

  btn_exit_ = btn_factory_.CreateButton(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.f + 25.f, static_cast<float>(window.getSize().y) / 2.f + 25.f),"Exit");
  btn_exit_->OnReleasedLeft = [&window]() {window.close();};


  //Create text
  give_amount_text_.setFont(font_);
  give_amount_text_.setString("Give Amount: " + std::to_string(give_amount_));
  give_amount_text_.setCharacterSize(12);
  give_amount_text_.setFillColor(sf::Color::Black);
  give_amount_text_.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) - 125.f, 225.f));

  dev_title_text_.setFont(font_);
  dev_title_text_.setString("Dev Menu \n (Give Resources)");
  dev_title_text_.setCharacterSize(12);
  dev_title_text_.setFillColor(sf::Color::Black);
  dev_title_text_.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) - 125.f, 25.f));

  ui_game_over_text_.setFont(font_);
  ui_game_over_text_.setString("Game Over");
  ui_game_over_text_.setCharacterSize(36);
  ui_game_over_text_.setFillColor(sf::Color::Black);
  ui_game_over_text_.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.f - 100, static_cast<float>(window.getSize().y) / 2.f - 50.f));

}
void UiManager::HandleEvents(std::optional<sf::Event> evt, bool &wasClicked, bool game_over) {
  //Handle the events depending on the ui state
  if (game_over) {
    btn_restart_->HandleEvent(evt, wasClicked);
    btn_exit_->HandleEvent(evt, wasClicked);
  }
  else {
    if (ui_) {
      btn_mine_->HandleEvent(evt, wasClicked);
      btn_lumber_->HandleEvent(evt, wasClicked);
      btn_windmill_->HandleEvent(evt, wasClicked);
      btn_cancel_->HandleEvent(evt, wasClicked);
      btn_dev_ui_->HandleEvent(evt, wasClicked);

      if (dev_ui_) {
        btn_give_wood_->HandleEvent(evt, wasClicked);
        btn_give_stone_->HandleEvent(evt, wasClicked);
        btn_give_food_->HandleEvent(evt, wasClicked);
        btn_add_give_amount_->HandleEvent(evt, wasClicked);
        btn_sub_give_amount_->HandleEvent(evt, wasClicked);
        btn_clear_->HandleEvent(evt, wasClicked);
        btn_kill_all_npc_->HandleEvent(evt, wasClicked);
      }
    }

    btn_ui_->HandleEvent(evt, wasClicked);
  }
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

  give_amount_text_.setString("Give Amount: " + std::to_string(give_amount_));
}
void UiManager::CreateFadingMessage(const std::string& text, sf::Vector2f pos, sf::Color color) {
  fading_messages_.emplace_back(font_, text, pos, color);
}

void UiManager::Draw(sf::RenderWindow& window, resources::StockManager& stock_manager, bool game_over) const {
  //Draw the ui elements depending on the ui state
  if (ui_) {

    for (auto& fading_message : fading_messages_) {
      fading_message.Draw(window);
    }

    //Draw backgrounds
    window.draw(ui_button_background_);
    window.draw(ui_resources_background_);

    //Draw the buttons
    btn_mine_->Draw(window);
    btn_lumber_->Draw(window);
    btn_windmill_->Draw(window);

    if (building_adding_type_ != buildings::BuildingsType::kNone) {
      btn_cancel_->Draw(window);
    }

    //Draw the stock
    stock_manager.Draw(window);

    //Draw the dev ui
    if (dev_ui_) {
      window.draw(ui_dev_button_background_);
      window.draw(dev_title_text_);
      btn_give_wood_->Draw(window);
      btn_give_stone_->Draw(window);
      btn_give_food_->Draw(window);
      window.draw(give_amount_text_);
      btn_add_give_amount_->Draw(window);
      btn_sub_give_amount_->Draw(window);
      btn_clear_->Draw(window);
      btn_kill_all_npc_->Draw(window);
    }

    btn_dev_ui_->Draw(window);

  }

  btn_ui_->Draw(window);

  if (game_over) {
    //Draw the game over window
    window.draw(ui_game_over_background_);
    window.draw(ui_game_over_text_);
    btn_restart_->Draw(window);
    btn_exit_->Draw(window);
  }
  else {
    //Draw the cursor indicator
    if (building_adding_type_ != buildings::BuildingsType::kNone) {
      cursor_indicator_.Draw(window);
    }
  }
}
}  // namespace api::ui