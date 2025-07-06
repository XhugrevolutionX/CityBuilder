//
// Created by sebas on 19/06/2025.
//

#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H
#include <iostream>

#include "npc_manager.h"

namespace api::ai {
    inline void CreateNpc(std::vector<std::unique_ptr<Npc>> &npcs, const NpcType type, sf::Vector2f& start_position, TileMap* tilemap, ResourceManager* ressource_manager){

      auto npc = std::make_unique<Npc>();

        switch (type) {
            case NpcType::kCyan:
                npc->Setup("Cyan","character_cyan.png", tilemap,start_position, ressource_manager, resources::ResourcesType::kWood);
                break;
            case NpcType::kRed:
                npc->Setup("Red","character_red.png", tilemap, start_position, ressource_manager, resources::ResourcesType::kStone);
                break;
            case NpcType::kLime:
                npc->Setup("Lime","character_lime.png", tilemap, start_position, ressource_manager, resources::ResourcesType::kFood);
                break;
          case NpcType::kPurple:
                npc->Setup("Purple","character_purple.png", tilemap, start_position, ressource_manager, resources::ResourcesType::kNone);
                break;
            default:
                std::cout << "Error: Npc type not found" << std::endl;
                break;
        }

      npcs.emplace_back(std::move(npc));

      if (type == NpcType::kCyan || type == NpcType::kLime || type == NpcType::kRed || type == NpcType::kPurple) {
        npcs.back()->SetPosition(start_position);
      }
    }
}


#endif //NPC_FACTORY_H
