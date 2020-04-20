#ifndef __BOTTOM_H__
#define __BOTTOM_H__

#include <cstddef>
#include <memory>
#include <vector>

#include "Tetrom.h"

struct Color {

  Color(unsigned char red, unsigned char green, unsigned char blue)
      : _blue(blue), _green(green), _red(red) {}

  unsigned char _red;
  unsigned char _blue;
  unsigned char _green;
};

const Color OColor = Color(255,255,255);
const Color IColor = Color(255,255,255);
const Color SColor = Color(255,255,255);
const Color LColor = Color(255,255,255);
const Color TColor = Color(255,255,255);


struct Cell {
  Point<int> p;
  Color color;
};

class Bottom {
public:
  Bottom(int gridWidth, int gridHeight);
  bool CheckIntersection(std::shared_ptr<Tetrom> tetrom);
  bool Add(std::shared_ptr<Tetrom> tetrom);

private:
  std::vector<Cell> _cells;
  int _gridWidth;
  int _gridHeight;
};

#endif // __BOTTOM_H__