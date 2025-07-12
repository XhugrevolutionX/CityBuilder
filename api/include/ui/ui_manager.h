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
#include "label_button.h"

namespace api::ui {

class UiManager {

  std::unique_ptr<LabelButton> btn_mine_;
  std::unique_ptr<LabelButton> btn_lumber_;
  std::unique_ptr<LabelButton> btn_windmill_;
  std::unique_ptr<Button> btn_cancel_;
  //std::unique_ptr<Button> btn_clear_;
  std::unique_ptr<Button> btn_ui_;


  ButtonFactory btn_factory_;

  sf::RectangleShape ui_button_background_;
  sf::RectangleShape ui_resources_background_;
  sf::Texture bg_ui_;

  CursorIndicator cursor_indicator_;

  bool ui_ = true;

public:
  buildings::BuildingsType building_adding_type_ = buildings::BuildingsType::kNone;

  void Setup(sf::RenderWindow& window, buildings::BuildingsManager* buildings_manager, TileMap* tilemap, ResourceManager* resource_manager, std::function<void(int, float, float, resources::ResourcesType)> ChopEvent);
  void HandleEvents(std::optional<sf::Event> evt, bool &wasClicked);
  void SetCursorTexture(TileMap* tilemap);
  void SetCursorPosition(sf::RenderWindow& window);
  void Draw(sf::RenderWindow& window, resources::stock_manager& stock_manager) const;

};

}

#endif //UI_MANAGER_H
