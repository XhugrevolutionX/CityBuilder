//
// Created by sebas on 19/06/2025.
//

#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H
#include <iostream>

#include "npc_manager.h"

namespace api::ai {
    inline void CreateNpc(std::vector<Npc> &npcs, const NpcType type, sf::Vector2f& start_position, TileMap* tilemap, RessourceManager& ressource_manager){
        npcs.emplace_back();

        switch (type) {
            case NpcType::kCyan:
                npcs.back().Setup("Cyan","character_cyan.png", tilemap,start_position, ressource_manager.GetRessources(Ressource::Type::kWood));
                break;
            case NpcType::kRed:
                npcs.back().Setup("Red","character_red.png", tilemap, start_position, ressource_manager.GetRessources(Ressource::Type::kStone));
                break;
            case NpcType::kLime:
                npcs.back().Setup("Lime","character_lime.png", tilemap, start_position, ressource_manager.GetRessources(Ressource::Type::kNone));
                break;
            case NpcType::kPurple:
                npcs.back().Setup("Purple","character_purple.png", tilemap, start_position, ressource_manager.GetRessources(Ressource::Type::kNone));
                break;
            default:
                std::cout << "Error: Npc type not found" << std::endl;
                break;
        }

      if (type == NpcType::kCyan || type == NpcType::kLime || type == NpcType::kRed || type == NpcType::kPurple) {
        npcs.back().SetPosition(start_position);
      }
    }
}


#endif //NPC_FACTORY_H
