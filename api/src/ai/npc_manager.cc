//
// Created by sebas on 19/06/2025.
//

#include "ai/npc_manager.h"
#include "ai/npc_factory.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif // TRACY_ENABLE

namespace api::ai {

  void NpcManager::Add(NpcType type, sf::Vector2f start_position, TileMap* tilemap, ResourceManager* ressource_manager, resources::StockManager* stock_manager) {
    CreateNpc(npcs_, type, start_position, tilemap, ressource_manager, stock_manager);
  }

    void NpcManager::Update(float dt){
    #ifdef TRACY_ENABLE
      ZoneScoped;
    #endif //TRACY_ENBALE
        for (auto& npc : npcs_) {
            npc->Update(dt);
        }
    }

    void NpcManager::Draw(sf::RenderWindow &window){
    #ifdef TRACY_ENABLE
        ZoneScoped;
    #endif //TRACY_ENBALE
        for (auto& npc : npcs_) {
            npc->Draw(window);
        }
    }

}
