#include <iostream>

#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "Tetrom.h"


int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{240};
  constexpr std::size_t kScreenHeight{400};
  constexpr std::size_t kGridWidth{12};
  constexpr std::size_t kGridHeight{20};

  //Update the Tetrom class
  Tetrom::gridWidth = kGridWidth;
  Tetrom::gridHeight = kGridHeight;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  
  
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";


  return 0;
}