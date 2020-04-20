#include "game.h"
#include "SDL.h"
#include <iostream>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()), random_w(0, static_cast<int>(grid_width)),
      random_t(0, static_cast<int>((int)TetromType::Count-1)) {

  CreateNewTetrom();
  _newTetrom = false;
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, _tetrom);
    Update();
    renderer.Render(_tetrom);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(_score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {
  if (_newTetrom) {
    CreateNewTetrom();
    _newTetrom = false;
  } else {
    if (!_tetrom->Move(MoveType::Down, 0.05)) {
      _newTetrom = true;
    }
  }
}

// Create the new tetrom
void Game::CreateNewTetrom() {
  // Get the tetrom randomly
  TetromType TT = (TetromType)random_t(engine);

  // Get initial point randomly
  Point<int> initPoint{0, 0};
  initPoint.x = random_w(engine);

  // TODO: get the initial state randomly

  // Create the new Teatrom
  switch (TT) {
  case TetromType::I:
    _tetrom = std::make_shared<ITetrom>(initPoint, 0);
    break;
  case TetromType::S:
    _tetrom = std::make_shared<STetrom>(initPoint, 0);
    break;
  case TetromType::T:
    _tetrom = std::make_shared<TTetrom>(initPoint, 0);
    break;
  case TetromType::O:
    _tetrom = std::make_shared<OTetrom>(initPoint, 0);
    break;
  case TetromType::L:
    _tetrom = std::make_shared<LTetrom>(initPoint, 0);
    break;
  default:
    throw "Out of range";
    break;
  }
}

int Game::GetScore() const { return _score; }