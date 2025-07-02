//
// Created by sebas on 26/06/2025.
//

#ifndef RESSOURCE_MANAGER_H
#define RESSOURCE_MANAGER_H
#include <vector>

#include "graphics/tilemap.h"
#include "ressource.h"

class RessourceManager {
	std::vector<ressource::Ressource> ressources_;

   public:
	void LoadRessources(
		ressource::RessourcesType type,
		std::vector<int> indexes,
		std::function<void(int, float)> OnChopEvent);

	[[nodiscard]] const std::vector<ressource::Ressource> GetRessources(
		ressource::RessourcesType type) const;
};

inline void RessourceManager::LoadRessources(
	ressource::RessourcesType type, std::vector<int> indexes,
	std::function<void(int, float)> OnChopEvent) {
	for (auto& index : indexes) {
		ressources_.emplace_back();
		ressources_.back().SetType(type);
		ressources_.back().SetIndex(index);
		ressources_.back().SetQuantity(10);
		ressources_.back().OnChopRessource_ = OnChopEvent;
	}
}

inline const std::vector<ressource::Ressource> RessourceManager::GetRessources(
	ressource::RessourcesType type) const {
	std::vector<ressource::Ressource> ressources_of_type = {};

	for (const auto& ressource : ressources_) {
		if (ressource.GetType() == type) {
			ressources_of_type.emplace_back(ressource);
		}
	}
	return ressources_of_type;
}

#endif	// RESSOURCE_MANAGER_H
