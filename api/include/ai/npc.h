﻿#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>

#include "graphics/tilemap.h"
#include "motion/motor.h"
#include "motion/path.h"
#include "npc_behaviour_tree.h"
#include "ressources/ressource.h"

using namespace core::ai::behaviour_tree;
using namespace api::motion;

namespace api::ai {
    class Npc {

        sf::Texture texture_;

      // Decision
      std::unique_ptr<NpcBehaviourTree> bt_tree_ =
              std::make_unique<NpcBehaviourTree>();

      // Movement
      static constexpr float kMovingSpeed = 200.0f;
      std::unique_ptr<motion::Motor> motor_ = std::make_unique<motion::Motor>();
      std::unique_ptr<motion::Path> path_ = std::make_unique<motion::Path>();

      // name
      std::string name_;

    public:
        void Setup(std::string_view name, std::string_view filename, TileMap* tilemap, sf::Vector2f& cantina_position, std::vector<Ressource> ressources);
        void Update(float dt);

        void Draw(sf::RenderWindow &window);

      void SetPosition(const sf::Vector2f& position) {
        motor_->SetPosition(position);
      }

    };
}

#endif //NPC_H
