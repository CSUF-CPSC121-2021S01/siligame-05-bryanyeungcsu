#include "game.h"
#include <iostream>
#include <memory>
#include <vector>
#include "opponent.h"
#include "player.h"

void Game::UpdateScreen() {
  graphics::Color white(255, 255, 255);
  GameScreen_.DrawRectangle(0, 0, 800, 600, white);
  for (int i = 0; i < Opponents_.size(); i++) {
    if (Opponents_[i]->GetIsActive()) {
      Opponents_[i]->Draw(GameScreen_);
    }
  }
  for (int i = 0; i < OpponentProjectiles_.size(); i++) {
    if (OpponentProjectiles_[i]->GetIsActive()) {
      OpponentProjectiles_[i]->Draw(GameScreen_);
    }
  }
  for (int i = 0; i < PlayerProjectiles_.size(); i++) {
    if (PlayerProjectiles_[i]->GetIsActive()) {
      PlayerProjectiles_[i]->Draw(GameScreen_);
    }
  }
  if (Myplayer_.GetIsActive()) {
    Myplayer_.Draw(GameScreen_);
  }
  GameScreen_.DrawText(10, 10, std::to_string(playerScore_), 35, 0, 0, 0);
}

void Game::CreateOpponents() {
  for (int i = 0; i < 5; i++) {
    Opponents_.push_back(std::make_unique<Opponent>(50 * i + 15, 50));
  }
}

bool Game::HasLost() { return Lost_; }

int Game::GetScore() { return playerScore_; }

void Game::Init() {
  GameScreen_.AddMouseEventListener(*this);
  GameScreen_.AddAnimationEventListener(*this);
  Myplayer_.SetX(20);
  Myplayer_.SetY(GameScreen_.GetHeight() - 50);
}

void Game::MoveGameElements() {
  for (int i = 0; i < Opponents_.size(); i++) {
    Opponents_[i]->Move(GameScreen_);
  }
  for (int j = 0; j < OpponentProjectiles_.size(); j++) {
    OpponentProjectiles_[j]->Move(GameScreen_);
  }
  for (int t = 0; t < PlayerProjectiles_.size(); t++) {
    PlayerProjectiles_[t]->Move(GameScreen_);
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < Opponents_.size(); i++) {
    if (Opponents_[i]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> oFire;
      oFire = std::make_unique<OpponentProjectile>();
      oFire->SetX(Opponents_[i]->GetX());
      oFire->SetY(Opponents_[i]->GetY());
      OpponentProjectiles_.push_back(std::move(oFire));
    }
  }
}

void Game::RemoveInactive() {
  for (int i = PlayerProjectiles_.size() - 1; i >= 0; i--) {
    if (!PlayerProjectiles_[i]->GetIsActive()) {
      PlayerProjectiles_.erase(PlayerProjectiles_.begin() + i);
    }
  }
  for (int i = OpponentProjectiles_.size() - 1; i >= 0; i--) {
    if (!OpponentProjectiles_[i]->GetIsActive()) {
      OpponentProjectiles_.erase(OpponentProjectiles_.begin() + i);
    }
  }
  for (int i = Opponents_.size() - 1; i >= 0; i--) {
    if (!Opponents_[i]->GetIsActive()) {
      Opponents_.erase(Opponents_.begin() + i);
    }
  }
}

void Game::OnAnimationStep() {
  if (Opponents_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  FilterIntersections();
  RemoveInactive();
  LaunchProjectiles();
  UpdateScreen();
  GameScreen_.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent &mouseEvent) {
  if (mouseEvent.GetX() > 0 && mouseEvent.GetY() &&
      mouseEvent.GetX() < GameScreen_.GetWidth() &&
      mouseEvent.GetY() < GameScreen_.GetHeight()) {
    Myplayer_.SetX(mouseEvent.GetX() - 25);
    Myplayer_.SetY(mouseEvent.GetY() - 25);
  }
  if (mouseEvent.GetMouseAction() == graphics::MouseAction::kPressed) {
    std::unique_ptr<PlayerProjectile> pFire =
        std::make_unique<PlayerProjectile>(mouseEvent.GetX(),
                                           mouseEvent.GetY() + 15);
    PlayerProjectiles_.push_back(std::move(pFire));
  }
  if (mouseEvent.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> pFire =
        std::make_unique<PlayerProjectile>(mouseEvent.GetX(),
                                           mouseEvent.GetY() + 15);
    PlayerProjectiles_.push_back(std::move(pFire));
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < Opponents_.size(); i++) {
    if (Myplayer_.IntersectsWith(Opponents_[i].get())) {
      Myplayer_.SetIsActive(false);
      Opponents_[i]->SetIsActive(false);
      Lost_ = true;
    }
  }
  for (int t = 0; t < PlayerProjectiles_.size(); t++) {
    for (int k = 0; k < Opponents_.size(); k++) {
      if (PlayerProjectiles_[t]->IntersectsWith(Opponents_[k].get()) == true) {
        PlayerProjectiles_[t]->SetIsActive(false);
        Opponents_[k]->SetIsActive(false);
        if (Myplayer_.GetIsActive()) {
          playerScore_++;
        }
      }
    }
  }
  for (int u = 0; u < OpponentProjectiles_.size(); u++) {
    if (OpponentProjectiles_[u]->IntersectsWith(&Myplayer_)) {
      Myplayer_.SetIsActive(false);
      OpponentProjectiles_[u]->SetIsActive(false);
      Lost_ = true;
    }
  }
}
