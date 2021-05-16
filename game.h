#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"

#ifndef GAME_H
#define GAME_H

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() { GameScreen_.Initialize(800, 600); }
  Game(int width, int height) { GameScreen_.Initialize(width, height); }

  graphics::Image &GetGameScreen() { return GameScreen_; }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return Opponents_; }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return OpponentProjectiles_;
  }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return PlayerProjectiles_;
  }
  Player &GetPlayer() { return Myplayer_; }
  void CreateOpponents();
  void Init();
  void UpdateScreen();
  void Start(graphics::Image &game) { GameScreen_.ShowUntilClosed("Test"); }
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep();
  void OnMouseEvent(const graphics::MouseEvent &mouseEvent);
  void RemoveInactive();
  void LaunchProjectiles();
  int GetScore();
  bool HasLost();

 private:
  graphics::Image GameScreen_;
  std::vector<std::unique_ptr<Opponent>> Opponents_;
  std::vector<std::unique_ptr<OpponentProjectile>> OpponentProjectiles_;
  std::vector<std::unique_ptr<PlayerProjectile>> PlayerProjectiles_;
  Player Myplayer_;
  int playerScore_ = 0;
  bool Lost_;
};

#endif
