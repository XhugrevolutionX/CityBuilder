#include "ai/npc.h"

#include <iostream>

#include <SFML/Graphics.hpp>

#include "ai/bt_sequence.h"
#include "ai/bt_selector.h"
#include "ai/bt_action.h"
#include "motion/AStar.h"

using namespace api::ai;

Status Npc::Move(){
    // if destination not reachable, return failure
    if (!path_.IsValid()) {
        std::cout << "Not reachable" << target_reachable_ << std::endl;
        return Status::kFailure;
    }
        if (!path_.IsDone()) {
          std::cout << "Move" << std::endl;
            // still arriving, return running
            return Status::kRunning;
        }
            // if destination reached, return success
            return Status::kSuccess;
    }

Status Npc::Eat(){
    std::cout << "I'm eating" << std::endl;
    // No failure, until we have food storage system
    hunger_ -= kHungerRate;
    if (hunger_ > 0) {
        return Status::kRunning;
    } else {
        SetNextPath();
        return Status::kSuccess;
    }
}

Status Npc::HungerBuild() {
    if (hunger_ >= 100) {
      std::cout << "I'm hungry, wanna eat........" << std::endl;
      return Status::kSuccess;
    } else {
      std::cout << "I'm not hungry, thanks........" << std::endl;
      return Status::kFailure;
    }
};

Status Npc::Work() {
  hunger_ += kHungerRate * 2;
  if (resourceAvailable_) {
    std::cout << "Resource Available, working....." << std::endl;
    return Status::kSuccess;
  }
  return Status::kFailure;
};

Status Npc::Sleep() {

  hunger_ += kHungerRate;
  std::cout << "I'm sleeping" << std::endl;
  return Status::kSuccess;
};

void Npc::SetupBehaviourTree(){
    auto feedSequence = std::make_unique<Sequence>();

    feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::HungerBuild, this)));
    feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::Eat, this)));
    feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::Move, this)));

    auto selector = std::make_unique<Selector>();
    // Attach the sequence to the selector
    selector->AddChild(std::move(feedSequence));
    selector->AddChild(std::make_unique<Action>(std::bind(&Npc::Work, this)));
    selector->AddChild(std::make_unique<Action>(std::bind(&Npc::Sleep, this)));

    root_ = std::move(selector);
}

void Npc::Setup(const TileMap* tileMap){
    textures.Load(files);

    SetupBehaviourTree();

    motor_.SetPosition({0, 0});
    motor_.SetSpeed(kMovingSpeed);

    tileMap_ = tileMap;
}

void Npc::Update(float dt){
    root_->Tick();
    if (path_.IsValid()){
        motor_.Update(dt);
        if (!path_.IsDone() && motor_.RemainingDistance() <= 0.001f) {
            motor_.SetDestination(path_.GetNextPoint());
        }
    }
}

void Npc::Draw(sf::RenderWindow &window){
    sf::Sprite sprite(textures.Get(Animation::KBlue));
    sprite.setPosition(motor_.GetPosition());
    window.draw(sprite);
}

void Npc::SetPath(const Path& path){
    path_ = path;
    motor_.SetDestination(path_.StartPoint());
}

void Npc::SetNextPath(){
  Path path;
  if (path_index_ < tileMap_->GetHouses().size() - 1) {
    path = ::motion::Astar::GetPath(tileMap_->GetHouses().at(path_index_), tileMap_->GetHouses().at(path_index_ + 1), tileMap_->GetWalkables());
    path_index_++;
  } else {
    path = ::motion::Astar::GetPath(tileMap_->GetHouses().at(path_index_), tileMap_->GetHouses().at(0), tileMap_->GetWalkables());
    path_index_ = 0;
  }
  SetPath(path);
}
