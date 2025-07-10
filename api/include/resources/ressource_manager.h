//
// Created by sebas on 26/06/2025.
//

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <memory>
#include <ranges>
#include <vector>

#include "graphics/tilemap.h"
#include "resources.h"

class ResourceManager {
	std::vector<std::shared_ptr<api::resources::Resource>> resources_;
	std::vector<int> visited_resources_;

   public:
        void Update(float dt, std::function<void(int index, api::resources::ResourcesType type)> OnGrow_);
	void LoadResources(api::resources::ResourcesType type, std::vector<int> indexes, std::function<void(int, float, float, api::resources::ResourcesType)> OnChopEvent);
        auto NearExploitableResource(sf::Vector2f pos, api::resources::ResourcesType type);
};

inline void ResourceManager::Update(float dt, std::function<void(int index, api::resources::ResourcesType type)> OnGrow_) {
  for (auto& resource : resources_) {
    resource->Update(dt, OnGrow_);
  }
}

inline void ResourceManager::LoadResources(
    api::resources::ResourcesType type, std::vector<int> indexes,
    std::function<void(int, float, float, api::resources::ResourcesType)> OnChopEvent) {

    const auto [first, last] = std::ranges::remove_if(resources_, [type] (std::shared_ptr<api::resources::Resource> r){return r->GetType() == type;});

    resources_.erase(first, last);

    for (auto& index : indexes) {
	    resources_.emplace_back(std::make_shared<api::resources::Resource>());
	    resources_.back()->SetType(type);
	    resources_.back()->SetIndex(index);
	    resources_.back()->OnChopRessource_ = OnChopEvent;

      switch (type) {
        case api::resources::ResourcesType::kWood:
          resources_.back()->SetQuantity(10);
          resources_.back()->SetRefillRate(0.3f);
          break;
        case api::resources::ResourcesType::kStone:
          resources_.back()->SetQuantity(20);
          resources_.back()->SetRefillRate(0.5f);

          break;
        case api::resources::ResourcesType::kFood:
          resources_.back()->SetQuantity(10);
          resources_.back()->SetRefillRate(0.25f);

          break;
        case api::resources::ResourcesType::kNone:
          resources_.back()->SetQuantity(0);
          resources_.back()->SetRefillRate(0.f);

          break;
        default:
          std::cerr << "Invalid resource type" << std::endl;
          break;

      }
    }
}

inline auto ResourceManager::NearExploitableResource(sf::Vector2f pos, api::resources::ResourcesType type) {
  auto filtered = resources_ | std::views::filter([type](std::shared_ptr<api::resources::Resource> r){return r->GetType() == type && r->GetQty() != 0;});

  std::vector sorted(filtered.begin(), filtered.end());

  std::ranges::sort(sorted, std::less{}, [pos](std::shared_ptr<api::resources::Resource> r){return TileMap::Distance(pos, TileMap::ScreenPosition(r->GetTileIndex()));});




  return sorted;
}

#endif	// RESOURCE_MANAGER_H
