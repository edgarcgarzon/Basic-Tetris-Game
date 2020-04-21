
#include <algorithm>
#include <iostream>

#include "Bottom.h"

Bottom::Bottom(int gridWidth, int gridHeight)
    : _gridHeight(gridHeight), _gridWidth(gridWidth) {

  auto c = Cell();
  _cells = std::vector<std::vector<Cell>>(
      _gridHeight, std::vector<Cell>(_gridWidth, Cell()));
}

// check if there is an intersection
Intersection Bottom::CheckIntersection(Tetrom *tetrom) {
  Intersection ret{false, false, false};
  for (auto p : tetrom->GetCurrPoints()) {
    // std::cout<<"Check point ("<<p.x<<","<<p.y<<") against";
    if (((p.y + 1) < _gridHeight) && cell(p.x, (p.y + 1)).filled) {
      ret.Down |= true;
    }
    if (((p.x - 1) > 0) && cell((p.x - 1), p.y).filled) {
      ret.Left |= true;
    }
    if (((p.x + 1) < _gridWidth) && cell((p.x + 1), p.y).filled) {
      ret.Right |= true;
    }
  }

  return ret;
}

// Add tatrom to bottom
bool Bottom::Add(Tetrom *tetrom) {
  Color tc(255, 255, 255);

  // Add all points to bottom
  for (auto p : tetrom->GetCurrPoints()) {
    cell(p.x, p.y).filled = true;
    cell(p.x, p.y).color = Color::GetTetromColor(tetrom->type);
  }
}

//Update the bottom
int Bottom::Update() {

  int removedRows = 0;
  
  std::remove_if(_cells.begin(), _cells.end(),
                 [&removedRows](std::vector<Cell> row) {
                   for (auto c : row) {
                     if (!c.filled) {
                       return false;
                     }
                   }
                   removedRows++;
                   return true;
                 });

  // Fill the last elements with a dummy cell as std::remove does not really
  // "erase the elements" neither change the dimension of the container
  if (removedRows > 0) {
    // create a new array with empty cells and concatenate cells
    auto temp = std::vector<std::vector<Cell>>(
        removedRows, std::vector<Cell>(_gridWidth, Cell()));
    temp.insert(temp.end(), _cells.begin(), (_cells.end() - removedRows));
    // replace _cells with the new vector
    _cells = std::move(temp);
  }

  /// return the number of delted rows
  return removedRows;
}

// check if all the cell in a row are filled
bool Bottom::RowFilled(int row) {
  for (auto c : _cells[row]) {
    if (!c.filled) {
      return false;
    }
  }
  return true;
}