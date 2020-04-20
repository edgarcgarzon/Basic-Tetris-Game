#include "controller.h"
#include "SDL.h"
#include <iostream>



void Controller::HandleInput(bool &running, Tetrom* tetrom) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        tetrom->SetPendingMove(MoveType::Turn);
        break;

      case SDLK_DOWN:
        tetrom->SetPendingMove(MoveType::Down);
        break;

      case SDLK_LEFT:
        tetrom->SetPendingMove(MoveType::Left);
        break;

      case SDLK_RIGHT:
        tetrom->SetPendingMove(MoveType::Right);
        break;
      
      default:
        tetrom->SetPendingMove(MoveType::None);
      break;
      }
    }
  }
}