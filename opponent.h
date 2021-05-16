#include <memory>
#include "game_element.h"

#ifndef OPPONENT_H
#define OPPONENT_H

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile(int x, int y) : GameElement(x, y, 50, 50) {}
  OpponentProjectile() : GameElement(0, 0, 50, 50) {}
  void Draw(graphics::Image &image);
  void Move(const graphics::Image &moveimage);
};

class Opponent : public GameElement {
 public:
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}
  Opponent() : GameElement(0, 0, 50, 50) {}
  void Draw(graphics::Image &image);
  void Move(const graphics::Image &moveimage);
  std::unique_ptr<OpponentProjectile> LaunchProjectile();

 private:
  int fireRate = 0;
};

#endif
