//
// Created by hugze on 06.07.2025.
//

#include <iostream>

#include "Stock.h"

#ifndef STOCKMANAGER_H
#define STOCKMANAGER_H

namespace api::resources {

class StockManager {

  Stock wood_ ;
  Stock stone_;
  Stock food_;

  Stock* selected_;

  void SelectStock(ResourcesType type);

  public:

  StockManager();

  int GetStock(ResourcesType type);
  void AddStock(ResourcesType type, int quantity);
  void RemoveStock(ResourcesType type, int quantity);

  void Draw(sf::RenderWindow &window) const;

};

inline StockManager::StockManager() : wood_(ResourcesType::kWood), stone_(ResourcesType::kStone), food_(ResourcesType::kFood) {}

inline void StockManager::SelectStock(ResourcesType type) {

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

inline int StockManager::GetStock(ResourcesType type) {

  SelectStock(type);
  return selected_->GetQuantity();

}

inline void StockManager::AddStock(ResourcesType type, int quantity) {

  SelectStock(type);
  selected_->AddQuantity(quantity);
}

inline void StockManager::RemoveStock(ResourcesType type, int quantity) {

  SelectStock(type);
  selected_->RemoveQuantity(quantity);
}


void StockManager::Draw(sf::RenderWindow &window) const {
  wood_.Draw(window);
  stone_.Draw(window);
  food_.Draw(window);
}
}





#endif //STOCKMANAGER_H
