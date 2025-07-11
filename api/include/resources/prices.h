//
// Created by hugze on 11.07.2025.
//

#ifndef PRICES_H
#define PRICES_H
#include <utility>

namespace api::resources {

class Prices {

  int wood_ = 0;
  int stone_ = 0;
  int food_ = 0;

public:

  void init(const int w, const int s, const int f) {wood_ = w; stone_ = s; food_ = f;};

  int wood() const { return wood_;};
  int stone() const { return stone_;};
  int food() const { return food_;};

  std::pair<int, int> GetPrice() const { return std::make_pair(wood_, stone_);};

};

}

#endif //PRICES_H
