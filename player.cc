#include "player.h"

void Player::Draw(graphics::Image &image) {
  graphics::Image playerImage;
  playerImage.Load("corgi.bmp");
  for (int i = 0; i < playerImage.GetHeight(); i++) {
    for (int j = 0; j < playerImage.GetWidth(); j++) {
      image.SetColor(GetX() + j, GetY() + i, playerImage.GetColor(j, i));
    }
  }
}

void Player::Move(const graphics::Image &moveimage) {}

void PlayerProjectile::Draw(graphics::Image &image) {
  graphics::Image playerProImage;
  playerProImage.Load("ajuumma.bmp");
  for (int i = 0; i < playerProImage.GetHeight(); i++) {
    for (int j = 0; j < playerProImage.GetWidth(); j++) {
      image.SetColor(GetX() + j, GetY() + i, playerProImage.GetColor(j, i));
    }
  }
}

void PlayerProjectile::Move(const graphics::Image &moveimage) {
  SetY(GetY() - 3);
  if (IsOutOfBounds(moveimage)) {
    SetIsActive(false);
  }
}
