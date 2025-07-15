//
// Created by hugze on 12.07.2025.
//

#ifndef UI_MANAGER_H
#define UI_MANAGER_H
#include <memory>

#include "buildings/buildings_manager.h"
#include "button.h"
#include "button_factory.h"
#include "cursor_indicator.h"
#include "fading_message.h"
#include "label_button.h"

namespace api::ui {

class UiManager {

  //Buttons
  ButtonFactory btn_factory_;

  //Gameplay Buttons
  std::unique_ptr<LabelButton> btn_mine_;
  std::unique_ptr<LabelButton> btn_lumber_;
  std::unique_ptr<LabelButton> btn_windmill_;
  std::unique_ptr<Button> btn_cancel_;
  std::unique_ptr<Button> btn_ui_;

  //Dev Buttons
  std::unique_ptr<Button> btn_dev_ui_;
  std::unique_ptr<Button> btn_clear_;
  std::unique_ptr<Button> btn_give_wood;
  std::unique_ptr<Button> btn_give_stone;
  std::unique_ptr<Button> btn_give_food;
  std::unique_ptr<Button> btn_add_give_amount;
  std::unique_ptr<Button> btn_sub_give_amount;
  int give_amount = 10;
  sf::Text give_amount_text_;
  sf::Text dev_title_text_;

  // Backgrounds
  sf::RectangleShape ui_button_background_;
  sf::RectangleShape ui_dev_button_background_;
  sf::RectangleShape ui_resources_background_;
  sf::Texture bg_stocks_;
  sf::Texture bg_buttons_;
  sf::Texture bg_dev_buttons_;

  //Cursor Indicator
  CursorIndicator cursor_indicator_;

  //Fading Messages
  sf::Font font_;
  std::vector<FadingMessage> fading_messages_;

  bool ui_ = true;
  bool dev_ui_ = false;

public:
  buildings::BuildingsType building_adding_type_ = buildings::BuildingsType::kNone;

  UiManager(): give_amount_text_(font_), dev_title_text_(font_) {};

  void Setup(sf::RenderWindow& window, buildings::BuildingsManager* buildings_manager, resources::StockManager* stock_manager, TileMap* tilemap, ResourceManager* resource_manager, std::function<void(int, float, float, resources::ResourcesType)> ChopEvent);
  void HandleEvents(std::optional<sf::Event> evt, bool &wasClicked);
  void SetCursorTexture(TileMap* tilemap);
  void Update(float dt, sf::RenderWindow& window);
  void CreateFadingMessage(const std::string& text, sf::Vector2f pos, sf::Color color = sf::Color::Black);
  void Draw(sf::RenderWindow& window, resources::StockManager& stock_manager) const;

};

}

#endif //UI_MANAGER_H
