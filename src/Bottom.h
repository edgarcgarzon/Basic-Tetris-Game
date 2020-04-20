#ifndef __BOTTOM_H__
#define __BOTTOM_H__

#include <cstddef>
#include <memory>
#include <vector>

#include "Point.h"
#include "Tetrom.h"
#include "Color.h"

struct Cell {
  bool filled;
  Color color;
};

class Bottom {
public:
  Bottom(int gridWidth, int gridHeight);
  Intersection CheckIntersection(Tetrom *tetrom);
  bool Add(Tetrom *tetrom);
  Cell &cell(int x, int y) { return _cells[y * _gridWidth + x]; }

  std::vector<Cell> _cells;

private:
  int _gridWidth;
  int _gridHeight;
};

#endif // __BOTTOM_H__