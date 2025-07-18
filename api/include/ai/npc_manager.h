//
// Created by sebas on 19/06/2025.
//

#ifndef NPC_MANAGER_H
#define NPC_MANAGER_H

#include "ai/npc.h"
#include "resources/ressource_manager.h"

namespace api::ai{

    enum class NpcType {
        kCyan,
        kRed,
        kLime,
        kPurple,
    };

    class NpcManager {

        std::vector<std::unique_ptr<Npc>> npcs_;

    public:
        void Add(NpcType type, sf::Vector2f start_position, TileMap* tilemap, ResourceManager* ressource_manager, resources::StockManager* stock_manager);
        void Update(float dt);
        void KillAll() { npcs_.clear(); }
        std::vector<std::unique_ptr<Npc>>* GetNpcs(){ return &npcs_; }
        void Draw(sf::RenderWindow &window);

    };
}



#endif //NPC_MANAGER_H
