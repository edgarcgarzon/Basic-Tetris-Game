#ifndef __BOTTOM_H__
#define __BOTTOM_H__

#include <cstddef>
#include <memory>
#include <vector>

#include "Point.h"
#include "Tetrom.h"
#include "Color.h"

struct Cell {
  Cell():filled(false), color(255,255,255){};
  bool filled;
  Color color;
};

class Bottom {
public:
  Bottom(int gridWidth, int gridHeight);
  Intersection CheckIntersection(Tetrom *tetrom);
  bool Add(Tetrom *tetrom);
  Cell &cell(int x, int y) { return _cells[y][x]; }
  int Update();
  bool CheckGameOver();

private:
  bool RowFilled(int row);

  int _gridWidth;
  int _gridHeight;

  std::vector<std::vector<Cell>> _cells;
};

#endif // __BOTTOM_H__