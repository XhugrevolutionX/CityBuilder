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
	std::vector<std::shared_ptr<api::resources::Resource>> ressources_;

   public:
	void LoadRessources(api::resources::ResourcesType type, std::vector<int> indexes, std::function<void(int, float, api::resources::ResourcesType)> OnChopEvent);
        auto NearExploitableResource(sf::Vector2f pos, api::resources::ResourcesType type);
};

inline void ResourceManager::LoadRessources(
    api::resources::ResourcesType type, std::vector<int> indexes,
    std::function<void(int, float, api::resources::ResourcesType)> OnChopEvent) {

    const auto [first, last] = std::ranges::remove_if(ressources_, [type] (std::shared_ptr<api::resources::Resource> r){return r->GetType() == type;});

    ressources_.erase(first, last);

    for (auto& index : indexes) {
	    ressources_.emplace_back(std::make_shared<api::resources::Resource>());
	    ressources_.back()->SetType(type);
	    ressources_.back()->SetIndex(index);
	    ressources_.back()->SetQuantity(10);
	    ressources_.back()->OnChopRessource_ = OnChopEvent;
    }
}

inline auto ResourceManager::NearExploitableResource(sf::Vector2f pos, api::resources::ResourcesType type) {
  auto filtered = ressources_ | std::views::filter([type](std::shared_ptr<api::resources::Resource> r){return r->GetType() == type && r->GetQty() != 0;});

  std::vector sorted(filtered.begin(), filtered.end());

  std::ranges::sort(sorted, std::less{}, [pos](std::shared_ptr<api::resources::Resource> r){return TileMap::Distance(pos, TileMap::ScreenPosition(r->GetTileIndex()));});




  return sorted;
}

#endif	// RESOURCE_MANAGER_H
