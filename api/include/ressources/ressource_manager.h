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
	void LoadRessources(
		ressource::RessourcesType type,
		std::vector<int> indexes,
		std::function<void(int, float)> OnChopEvent);

	//[[nodiscard]] const auto GetRessources(ressource::RessourcesType type) const;

        auto NearResource(sf::Vector2f pos, ressource::RessourcesType type);
};

inline void RessourceManager::LoadRessources(
	ressource::RessourcesType type, std::vector<int> indexes,
	std::function<void(int, float)> OnChopEvent) {
	for (auto& index : indexes) {
		ressources_.emplace_back(std::make_shared<ressource::Ressource>());
		ressources_.back()->SetType(type);
		ressources_.back()->SetIndex(index);
		ressources_.back()->SetQuantity(10);
		ressources_.back()->OnChopRessource_ = OnChopEvent;
	}
}

// inline const auto RessourceManager::GetRessources(
// 	ressource::RessourcesType type) const {
//
//         return ressources_ | std::views::filter([type](std::shared_ptr<ressource::Ressource> r){return r->GetType() == type;});
//
// 	// std::vector<std::shared_ptr<ressource::Ressource>> ressources_of_type = {};
// 	//
// 	// for (const auto& ressource : ressources_) {
// 	// 	if (ressource->GetType() == type) {
// 	// 		ressources_of_type.emplace_back(ressource);
// 	// 	}
// 	// }
// 	// return ressources_of_type;
// }

inline auto RessourceManager::NearResource(sf::Vector2f pos, ressource::RessourcesType type) {
  auto filtered = ressources_ | std::views::filter([type](std::shared_ptr<ressource::Ressource> r){return r->GetType() == type;});

  std::vector sorted(filtered.begin(), filtered.end());

  std::ranges::sort(sorted, std::less{}, [pos](std::shared_ptr<ressource::Ressource> r){return TileMap::Distance(pos, TileMap::ScreenPosition(r->GetTileIndex()));});

  return sorted;
}

#endif	// RESSOURCE_MANAGER_H
