#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>

#include "ai/bt_node.h"
#include "assets/asset_manager.h"
#include "graphics/tilemap.h"
#include "motion/motor.h"
#include "motion/path.h"

using namespace core::ai::behaviour_tree;
using namespace api::motion;

namespace api::ai {
    class Npc {

        sf::Texture texture_;

        // Behaviour tree
        std::unique_ptr<Node> root_;
        // Behaviour Constants
        static constexpr float kHungerRate = 0.5f;
        static constexpr float kMovingSpeed = 50.0f;

        // Motion
        Motor motor_;
        Path path_;

        // Tilemap
        const TileMap* tileMap_;

    public:
        void Setup(std::string_view fileName, const TileMap* tileMap);
        void Update(float dt);

        void Draw(sf::RenderWindow &window);

        // Actions
        Status Move();
        Status HungerBuild();
        Status Eat();
        Status Work();
        Status Sleep();

        void SetupBehaviourTree();

        // Behaviours
        float hunger_ = 0;
        bool resourceAvailable_ = true;
        bool target_reachable_ = true;
        float target_distance_ = 20;


        float path_index_ = 0;

        // Motion
        void SetPath(const Path& path);
        void SetNextPath();

    };
}

#endif //NPC_H
