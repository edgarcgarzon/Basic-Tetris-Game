#include "controller.h"
#include "SDL.h"
#include <iostream>



void Controller::HandleInput(bool &running, std::shared_ptr<Tetrom> tetrom) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        tetrom->Turn(TurnType::CW);
        break;

      case SDLK_DOWN:
        tetrom->Move(MoveType::Down, 1);
        break;

      case SDLK_LEFT:
        tetrom->Move(MoveType::Left, 1);
        break;

      case SDLK_RIGHT:
        tetrom->Move(MoveType::Right, 1);
        break;
      }
    }
  }
}