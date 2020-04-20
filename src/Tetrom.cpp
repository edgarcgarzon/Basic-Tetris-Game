

#include "Tetrom.h"

int Tetrom::gridWidth = 20;
int Tetrom::gridHeight = 20;

Tetrom::Tetrom(Point<int> initPos, int initState, TetromType type,
               std::vector<std::vector<Point<int>>> states)
    : _currPos({(float)initPos.x, (float)initPos.y}), _currState(initState),
      _type(type), _states(states) {

  // Check if current position is inside the grid
  if (!TetromInGridRange()) {
    // TODO: improuve correction
    _currPos = {0, 0};
  }
}

// Check if the current position is with-in the grid's dimension
bool Tetrom::TetromInGridRange() const {
  Point p = GetMaxXY();
  if (p.x >= gridWidth)
    return false;
  if (p.y >= gridHeight)
    return false;

  p = GetMinXY();
  if (p.x < 0)
    return false;
  if (p.y < 0)
    return false;

  return true;
}

// Get a point with the maximum values of the current state of the tetrom
Point<int> Tetrom::GetMaxXY() const {
  Point<int> pMax{0, 0};
  for (auto p : _states[_currState]) {
    if (p.x + (int)_currPos.x > pMax.x)
      pMax.x = p.x + (int)_currPos.x;
    if (p.y + (int)_currPos.y > pMax.y)
      pMax.y = p.y + (int)_currPos.y;
  }
  return pMax;
}

// Get a point with the minium values of the current state of the tetrom
Point<int> Tetrom::GetMinXY() const {
  Point<int> pMin{gridWidth, gridHeight};
  for (auto p : _states[_currState]) {
    if (p.x + (int)_currPos.x < pMin.x)
      pMin.x = p.x + (int)_currPos.x;
    if (p.y + (int)_currPos.y < pMin.y)
      pMin.y = p.y + (int)_currPos.y;
  }
  return pMin;
}

// Return the current points according to current position
std::vector<Point<int>> Tetrom::GetCurrPoints() const {
  std::vector<Point<int>> retV;

  for (auto p : _states[_currState]) {
    retV.emplace_back(p + Point<int>(_currPos));
  }

  return std::move(retV);
}

// Move tetrom according to direction and speed, if the final position is out of
// the range of the grid: the function return false and does not affect the
// tetrom
bool Tetrom::Move(MoveType moveType, float speed) {

  Point<float> tempCurrPos = _currPos;

  switch (moveType) {
  case MoveType::Down:
    _currPos.y += speed;
    break;

  case MoveType::Left:
    _currPos.x -= speed;
    break;

  case MoveType::Right:
    _currPos.x += speed;
    break;

  default:
    return false;
  }

  if (!TetromInGridRange()) {
    // restore the old current position as it out of the grid range
    _currPos = tempCurrPos;
    return false;
  }

  return true;
}

// Turn tetrom according to turn-type, if the final position is out of the range
// of the grid the function return false and does not affect the tetrom
bool Tetrom::Turn(TurnType turnType) {
  float _tempCurrState = _currState;

  // Move the index
  if (turnType == TurnType::CW) {
    _currState += 1;
  } else {
    _currState -= 1;
  }

  // check index in the range
  if (_currState < 0) {
    _currState = _states.size() - 1;
  } else if (_currState >= _states.size()) {
    _currState = 0;
  }

  // check that tetrom is on the grid range
  if (!TetromInGridRange()) {
    _currState = _tempCurrState;
    return false;
  }

  return true;
}
