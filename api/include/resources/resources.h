//
// Created by sebas on 26/06/2025.
//

#ifndef RESOURCES_H
#define RESOURCES_H

#include <algorithm>
#include <functional>
namespace api::resources {

enum class ResourcesType {
  kNone, kWood, kStone, kFood
};

class Resource {

private:
  int tile_index_ = 0;
  float quantity_ = 0;
  ResourcesType type_ = ResourcesType::kNone;
  double cut_time_ = 0;

public:
  [[nodiscard]] ResourcesType GetType() const;
  [[nodiscard]] int GetTileIndex() const;
  [[nodiscard]] float GetQty() const;

  void SetType(ResourcesType type);
  void SetIndex(int index);
  void SetQuantity(float quantity);

  void Exploit(float);

  std::function<void(int, float, resources::ResourcesType)> OnChopRessource_ = nullptr;

};

inline void Resource::SetType(ResourcesType type){
  type_ = type;
}
inline void Resource::SetIndex(int index){
  tile_index_ = index;
}
inline void Resource::SetQuantity(float quantity){
  quantity_ = quantity;
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
  quantity_ -= rate;
  quantity_ = std::max<float>(quantity_, 0);

  if (OnChopRessource_) {
    OnChopRessource_(tile_index_, quantity_, type_);
  }
}
}

#endif //RESOURCES_H
