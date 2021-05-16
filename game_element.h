#include <iostream>
#include "cpputils/graphics/image.h"

#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

class GameElement {
 public:
  int GetX() const { return x_; }
  void SetX(int x) { x_ = x; }
  int GetY() const { return y_; }
  void SetY(int y) { y_ = y; }
  int GetWidth() const { return kWidth_; }
  int GetHeight() const { return kHeight_; }
  bool GetIsActive() const { return is_active_; }
  void SetIsActive(bool active) { is_active_ = active; }
  GameElement() : x_(0), y_(0), kWidth_(50), kHeight_(50) {}
  GameElement(int x, int y, int kWidth, int kHeight)
      : x_(x), y_(y), kWidth_(kWidth), kHeight_(kHeight), is_active_(true) {}
  virtual void Draw(graphics::Image &image) = 0;
  virtual void Move(const graphics::Image &moveimage) = 0;
  bool IntersectsWith(GameElement *element);
  bool IsOutOfBounds(const graphics::Image &boundimage);

 private:
  int x_;
  int y_;
  int kWidth_;
  int kHeight_;
  bool is_active_;
};

#endif
