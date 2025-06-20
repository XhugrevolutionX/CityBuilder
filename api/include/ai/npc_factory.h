//
// Created by sebas on 19/06/2025.
//

#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H
#include "npc_manager.h"

namespace api::ai {
    inline void CreateNpc(std::vector<Npc> &npcs, NpcType type, const TileMap *tilemap){
        npcs.emplace_back();

        switch (type) {
            case NpcType::kCyan:
                npcs.back().Setup("character_cyan.png", tilemap);
                break;
            case NpcType::kRed:
                npcs.back().Setup("character_red.png", tilemap);
                break;
            case NpcType::kLime:
                npcs.back().Setup("character_lime.png", tilemap);
                break;
            case NpcType::kPurple:
                npcs.back().Setup("character_purple.png", tilemap);
                break;
            default:
                break;
        }
    }
}


#endif //NPC_FACTORY_H
