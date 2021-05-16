#include "game_element.h"

bool GameElement::IntersectsWith(GameElement *element) {
  return !(GetX() > (*element).GetX() + (*element).GetWidth() ||
           (*element).GetX() > GetX() + GetWidth() ||
           GetY() > (*element).GetY() + (*element).GetHeight() ||
           (*element).GetY() > GetY() + GetHeight());
}

bool GameElement::IsOutOfBounds(const graphics::Image &boundimage) {
  if (GetX() < 0 || GetX() + GetWidth() > boundimage.GetWidth()) {
    return true;
  } else if (GetY() < 0 || GetY() + GetHeight() > boundimage.GetHeight()) {
    return true;
  } else {
    return false;
  }
}
