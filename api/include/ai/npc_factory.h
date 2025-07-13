//
// Created by sebas on 19/06/2025.
//

#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H
#include <iostream>
#include "npc_manager.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif // TRACY_ENABLE

namespace api::ai {
    inline void CreateNpc(std::vector<std::unique_ptr<Npc>> &npcs, const NpcType type, sf::Vector2f& start_position, TileMap* tilemap, ResourceManager* ressource_manager, resources::StockManager* stock_manager){

      #ifdef TRACY_ENABLE
      ZoneScoped;
      #endif //TRACY_ENBALE
      auto npc = std::make_unique<Npc>();

        switch (type) {
            case NpcType::kCyan:
                npc->Setup("Cyan","character_cyan.png", tilemap,start_position, ressource_manager, resources::ResourcesType::kWood, stock_manager);
                break;
            case NpcType::kRed:
                npc->Setup("Red","character_red.png", tilemap, start_position, ressource_manager, resources::ResourcesType::kStone, stock_manager);
                break;
            case NpcType::kLime:
                npc->Setup("Lime","character_lime.png", tilemap, start_position, ressource_manager, resources::ResourcesType::kFood, stock_manager);
                break;
            case NpcType::kPurple:
                npc->Setup("Purple","character_purple.png", tilemap, start_position, ressource_manager, resources::ResourcesType::kNone, stock_manager);
                break;
            default:
                std::cerr << "Error: Npc type not found" << std::endl;
                break;
        }

      npcs.emplace_back(std::move(npc));

      if (type == NpcType::kCyan || type == NpcType::kLime || type == NpcType::kRed || type == NpcType::kPurple) {
        npcs.back()->SetPosition(start_position);
      }
    }
}


#endif //NPC_FACTORY_H
