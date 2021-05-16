#include "opponent.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameElement {
 public:
  Player(int x, int y) : GameElement(x, y, 50, 50) {}
  Player() : GameElement(0, 0, 50, 50) {}
  void Move(const graphics::Image &moveimage);
  void Draw(graphics::Image &image);
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile(int x, int y) : GameElement(x, y, 50, 50) {}
  PlayerProjectile() : GameElement(0, 0, 50, 50) {}
  void Draw(graphics::Image &image);
  void Move(const graphics::Image &moveimage);
};

#endif
