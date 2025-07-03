//
// Created by sebas on 26/06/2025.
//

#ifndef RESSOURCE_MANAGER_H
#define RESSOURCE_MANAGER_H
#include <memory>
#include <ranges>
#include <vector>

#include "graphics/tilemap.h"
#include "ressource.h"

class RessourceManager {
	std::vector<std::shared_ptr<ressource::Ressource>> ressources_;

   public:
	void LoadRessources(ressource::RessourcesType type, std::vector<int> indexes, std::function<void(int, float)> OnChopEvent);
        auto NearExploitableResource(sf::Vector2f pos, ressource::RessourcesType type);
};

inline void RessourceManager::LoadRessources(
    ressource::RessourcesType type, std::vector<int> indexes,
    std::function<void(int, float)> OnChopEvent) {

    const auto [first, last] = std::ranges::remove_if(ressources_, [type] (std::shared_ptr<ressource::Ressource> r){return r->GetType() == type;});

    ressources_.erase(first, last);

    for (auto& index : indexes) {
	    ressources_.emplace_back(std::make_shared<ressource::Ressource>());
	    ressources_.back()->SetType(type);
	    ressources_.back()->SetIndex(index);
	    ressources_.back()->SetQuantity(10);
	    ressources_.back()->OnChopRessource_ = OnChopEvent;
    }
}

inline auto RessourceManager::NearExploitableResource(sf::Vector2f pos, ressource::RessourcesType type) {
  auto filtered = ressources_ | std::views::filter([type](std::shared_ptr<ressource::Ressource> r){return r->GetType() == type && r->GetQty() != 0;});

  std::vector sorted(filtered.begin(), filtered.end());

  std::ranges::sort(sorted, std::less{}, [pos](std::shared_ptr<ressource::Ressource> r){return TileMap::Distance(pos, TileMap::ScreenPosition(r->GetTileIndex()));});




  return sorted;
}

#endif	// RESSOURCE_MANAGER_H
