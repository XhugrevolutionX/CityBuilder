﻿//
// Created by sebas on 19/06/2025.
//

#ifndef NPC_MANAGER_H
#define NPC_MANAGER_H

#include "ai/npc.h"

namespace api::ai{

    enum class NpcType {
        kCyan,
        kRed,
        kLime,
        kPurple
    };

    class NpcManager {

        std::vector<Npc> npcs_;

    public:
        void Add(NpcType type, const TileMap* tilemap);
        void Update(float dt);
        void Draw(sf::RenderWindow &window);

    };
}



#endif //NPC_MANAGER_H
