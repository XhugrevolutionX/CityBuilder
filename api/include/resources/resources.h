//
// Created by sebas on 26/06/2025.
//

#ifndef RESOURCES_H
#define RESOURCES_H

#include <algorithm>
#include <functional>
#include <iostream>
namespace api::resources {

enum class ResourcesType {
  kNone, kWood, kStone, kFood
};

class Resource {

private:
  int tile_index_ = 0;
  float quantity_ = 0;
  float total_quantity_ = 0;
  ResourcesType type_ = ResourcesType::kNone;
  double cut_time_ = 0;
  double refill_rate_ = 0.2;
  float growth_;


public:
  bool cutted_ = false;

  [[nodiscard]] ResourcesType GetType() const;
  [[nodiscard]] int GetTileIndex() const;
  [[nodiscard]] float GetQty() const;

  void SetType(ResourcesType type);
  void SetIndex(int index);
  void SetQuantity(float quantity);
  void SetRefillRate(float rate);

  void Exploit(float);

  void Update(float dt, std::function<void(int index, ResourcesType type)> OnGrow_);

  std::function<void(int, float, float, ResourcesType)> OnChopRessource_ = nullptr;

};

inline void Resource::Update(float dt, std::function<void(int index, ResourcesType type)> OnGrow_) {
  if (cutted_) {
    if (growth_ < total_quantity_) {
      growth_ += dt * refill_rate_;
      //std::cout << "refill " << growth_ << "\n";
    }
    else {
      growth_ = 0;
      quantity_ = total_quantity_;
      cutted_ = false;
      OnGrow_(tile_index_, type_);
    }
  }
}

inline void Resource::SetType(ResourcesType type){
  type_ = type;
}
inline void Resource::SetIndex(int index){
  tile_index_ = index;
}
inline void Resource::SetQuantity(float quantity) {
  quantity_ = quantity;
  total_quantity_ = quantity;
}
inline void Resource::SetRefillRate(float rate) {
  refill_rate_ = rate;
}
inline ResourcesType Resource::GetType() const{
  return type_;
}
inline int Resource::GetTileIndex() const {
  return tile_index_;
}
inline float Resource::GetQty() const {
  return quantity_;
}


inline void Resource::Exploit(float rate) {
  if (type_ == ResourcesType::kFood)
  {
    quantity_ -= rate / 2;
  }
  else
    {
    quantity_ -= rate;

  }
  quantity_ = std::max<float>(quantity_, 0);

  if (OnChopRessource_) {
    OnChopRessource_(tile_index_, total_quantity_, quantity_, type_);
  }
}
}

#endif //RESOURCES_H
