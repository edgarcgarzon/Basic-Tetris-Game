#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "Tetrom.h"
#include "Bottom.h"


class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;

private:
  std::unique_ptr<Tetrom> _tetrom;
  std::unique_ptr<Bottom> _bottom;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_t;

  bool _newTetrom;
  int _score{0};

  void Update();
  void CreateNewTetrom();
};

#endif