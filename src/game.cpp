#include "game.h"
#include "SDL.h"
#include <iostream>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()), 
    random_w(0, static_cast<int>(grid_width)),
    random_t(0, static_cast<int>((int)TetromType::Count-1)){
  
  _bottom = std::make_unique<Bottom>(grid_width, grid_height);
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
    controller.HandleInput(running, _tetrom.get());
    Update();
    renderer.Render(_tetrom.get(), _bottom.get());

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
      _bottom->Add(_tetrom.get());
      _newTetrom = true;
    }
    else 
    {
      // Check for intersection and get move type
      Intersection I = _bottom->CheckIntersection(_tetrom.get());
      MoveType mt = _tetrom->GetPendingMove();
      
      //If intersection down
      if(I.Down)
      {
        //add it to bottom
        _bottom->Add(_tetrom.get());
        _newTetrom = true;
      }
      else if(I.Right && mt == MoveType::Right)
      {
        /* do nothing as there are blocks at the right that does not allow movement */
      }
      else if(I.Left && mt == MoveType::Left)
      {
        /* do nothing as there are blocks at the left that does not allow movement */
      }
      else
      {
        // apply the movement
        _tetrom->Move(mt, 1);
      }

      _tetrom->SetPendingMove(MoveType::None);

      //remove the filled rows and increment the score
      _score += _bottom->Update();
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
    _tetrom = std::make_unique<ITetrom>(initPoint, 0);
    break;
  case TetromType::S:
    _tetrom = std::make_unique<STetrom>(initPoint, 0);
    break;
  case TetromType::T:
    _tetrom = std::make_unique<TTetrom>(initPoint, 0);
    break;
  case TetromType::O:
    _tetrom = std::make_unique<OTetrom>(initPoint, 0);
    break;
  case TetromType::L:
    _tetrom = std::make_unique<LTetrom>(initPoint, 0);
    break;
  default:
    throw "Out of range";
    break;
  }
}

int Game::GetScore() const { return _score; }