//
// Created by karol on 28.03.2025.
//
#include <iostream>
#include <windows.h>
#include "include/Gameplay.h"

using namespace std;

int main() {
  SetConsoleOutputCP(CP_UTF8);
  srand(time(NULL));

  Gameplay game;
  game.startGame();

  return 0;
}