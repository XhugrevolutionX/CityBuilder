﻿//
// Created by sebas on 19/06/2025.
//

#ifndef NPC_BEHAVIOUR_TREE_H
#define NPC_BEHAVIOUR_TREE_H

#include <memory>

#include "ai/bt_node.h"
#include "graphics/tilemap.h"
#include "motion/motor.h"
#include "motion/path.h"
#include "resources/ressource_manager.h"
#include "resources/stock_manager.h"

namespace api::ai {
class NpcBehaviourTree {
	// Behaviour tree
	std::unique_ptr<core::ai::behaviour_tree::Node> bt_root_;

	// Env informations ----------------------
	TileMap* tilemap_ = nullptr;
	// Ways of action
	motion::Motor* npc_motor_ = nullptr;
	motion::Path* path_ = nullptr;

	void SetDestination(const sf::Vector2f& destination);
	// Actions
	[[nodiscard]] core::ai::behaviour_tree::Status CheckHunger();
	[[nodiscard]] core::ai::behaviour_tree::Status Move();
	[[nodiscard]] core::ai::behaviour_tree::Status Eat();
	[[nodiscard]] core::ai::behaviour_tree::Status PickResource();
	[[nodiscard]] core::ai::behaviour_tree::Status GetResource();
	[[nodiscard]] core::ai::behaviour_tree::Status Idle();


	// Behaviour Constants
	static constexpr float kHungerRate = 4.f;
	static constexpr float kExploitRate = 2.f;
        static constexpr float kEatRate = 10.f;

	// Behaviours
	float hunger_ = 0.0f;
	bool resourceAvailable_ = true;
	float tick_dt = 0;

	sf::Vector2f cantina_position_;
	ResourceManager* ressources_;
	resources::stock_manager* stocks_;
        resources::ResourcesType resource_type_;
	std::shared_ptr<resources::Resource> current_ressource_;

   public:
	void SetupBehaviourTree(motion::Motor* npc_motor, motion::Path* path, TileMap* tilemap, sf::Vector2f cantina_position, ResourceManager* ressources, resources::ResourcesType type, resources::stock_manager* stock_manager);
	void Update(float dt);
        float GetHunger();
};
}  // namespace api::ai

#endif	// NPC_BEHAVIOUR_TREE_H
