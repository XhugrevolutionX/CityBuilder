//
// Created by hugze on 06.07.2025.
//

#include <iostream>

#include "Stock.h"

#ifndef STOCKMANAGER_H
#define STOCKMANAGER_H

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif // TRACY_ENABLE

namespace api::resources {

class stock_manager {

  Stock wood_ ;
  Stock stone_;
  Stock food_;

  Stock* selected_;

  void SelectStock(ResourcesType type);

  public:

  stock_manager();

  int GetStock(ResourcesType type);
  void AddStock(ResourcesType type, int quantity);
  void RemoveStock(ResourcesType type, int quantity);

  void Draw(sf::RenderWindow &window) const;

};

inline stock_manager::stock_manager() : wood_(ResourcesType::kWood, 150), stone_(ResourcesType::kStone, 100), food_(ResourcesType::kFood, 100) {}

inline void stock_manager::SelectStock(ResourcesType type) {

  switch (type) {
    case ResourcesType::kWood:
      selected_ = &wood_;
    break;
    case ResourcesType::kStone:
      selected_ = &stone_;
    break;
    case ResourcesType::kFood:
      selected_ = &food_;
    break;
    case ResourcesType::kNone:
      std::cerr << "Invalid Stock type" << std::endl;
    break;
  }
}

inline int stock_manager::GetStock(ResourcesType type) {

  SelectStock(type);
  return selected_->GetQuantity();

}

inline void stock_manager::AddStock(ResourcesType type, int quantity) {

  SelectStock(type);
  selected_->AddQuantity(quantity);
}

inline void stock_manager::RemoveStock(ResourcesType type, int quantity) {

  SelectStock(type);
  selected_->RemoveQuantity(quantity);
}


inline void stock_manager::Draw(sf::RenderWindow &window) const {
  #ifdef TRACY_ENABLE
    ZoneScoped;
  #endif //TRACY_ENBALE
  wood_.Draw(window);
  stone_.Draw(window);
  food_.Draw(window);
}
}

#endif //STOCKMANAGER_H
