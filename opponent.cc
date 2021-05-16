#include "opponent.h"

#include "cpputils/graphics/image.h"

void Opponent::Draw(graphics::Image &image) {
  graphics::Image opponentImage;
  opponentImage.Load("slime.bmp");
  for (int i = 0; i < opponentImage.GetHeight(); i++) {
    for (int j = 0; j < opponentImage.GetWidth(); j++) {
      image.SetColor(GetX() + j, GetY() + i, opponentImage.GetColor(j, i));
    }
  }
}

void Opponent::Move(const graphics::Image &moveimage) {
  SetY(GetY() + 1);
  SetX(GetX() + 1);
  if (IsOutOfBounds(moveimage)) {
    SetIsActive(false);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  if (fireRate >= 15) {
    fireRate = 0;
    std::unique_ptr<OpponentProjectile> projectile;
    projectile = std::make_unique<OpponentProjectile>();
    return std::move(projectile);
  } else {
    fireRate++;
    return nullptr;
  }
}

void OpponentProjectile::Draw(graphics::Image &image) {
  graphics::Image opponentProImage;
  opponentProImage.Load("hint.bmp");
  for (int i = 0; i < opponentProImage.GetHeight(); i++) {
    for (int j = 0; j < opponentProImage.GetWidth(); j++) {
      image.SetColor(GetX() + j, GetY() + i, opponentProImage.GetColor(j, i));
    }
  }
}
void OpponentProjectile::Move(const graphics::Image &moveimage) {
  SetY(GetY() + 3);
  SetX(GetX() + 2);
  if (IsOutOfBounds(moveimage)) {
    SetIsActive(false);
  }
}
