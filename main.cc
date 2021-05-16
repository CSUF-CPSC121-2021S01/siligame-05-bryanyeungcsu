#include <iostream>
#include "game.h"

int main() {
  Game PlayGame;
  PlayGame.Init();
  PlayGame.Start(PlayGame.GetGameScreen());
  return 0;
}
