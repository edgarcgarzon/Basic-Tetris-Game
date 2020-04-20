#ifndef __TETROM_H__
#define __TETROM_H__

#include <vector>

template <class T> struct Point {
  T x;
  T y;

  // Overload operator
  Point operator+(const Point &a) const { return Point<T>{a.x + x, a.y + y}; }
  Point& operator+=(const Point &a){x += a.x; y += a.y;}
  Point operator-(const Point &a) const { return Point<T>{a.x - x, a.y - y}; }
  Point& operator-=(const Point &a){x -= a.x; y -= a.y;}
  bool operator==(const Point &a) const { return (x == a.x && y == a.y); }
  operator Point<int>() const {
    return Point<int>{static_cast<int>(x), static_cast<int>(y)};
  }
  bool neighbour(Point p){
    if((p.x + 1 == x) || (p.x - 1 == x)){return true;}
    if((p.y + 1 == y) || (p.y - 1 == y)){return true;}
    return false;
  }
};

enum class TetromType { L, S, T, O, I, Count };

enum class TurnType {
  CW = 0, // clock-wise
  CCW     // Counter clock-wise
};

enum class MoveType {
  Down = 0,
  Left,
  Right,

};

class Tetrom {
public:
  // Tetrom() : Tetrom({0, 0}, 0, {}) {} // Dummy constructor shall not be used
  bool Move(MoveType moveType, float speed);
  bool Turn(TurnType turnType);
  std::vector<Point<int>> GetCurrPoints() const;
  
  TetromType type;

  // static members
  static int gridWidth;  // This member shall be set before the any objec
                         // instance
  static int gridHeight; // This member shall be set before the any objec
                         // instance

protected:
  Tetrom(Point<int> initPos, int initState, TetromType tetromType,
         std::vector<std::vector<Point<int>>> states);

  virtual void ReBase() = 0;  //This function will re-base the current position(_currPos)
  int _currState;
  Point<float> _currPos;

private:
  bool TetromInGridRange() const;
  bool TryReBase();
  Point<int> GetMaxXY() const;
  Point<int> GetMinXY() const;


  const std::vector<std::vector<Point<int>>> _states;
};

/*
(0)     (1)     (2)     (3)
X 0 0   0 0 0   0 X X   X X X
X 0 0   0 0 X   0 0 X   X 0 0
X X 0   X X X   0 0 X   0 0 0
*/
class LTetrom : public Tetrom {
public:
  LTetrom(Point<int> initPos, int initState)
      : Tetrom(initPos, initState, TetromType::L,
               {
                   {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
                   {{0, 2}, {1, 2}, {2, 2}, {2, 1}},
                   {{2, 2}, {2, 1}, {2, 0}, {1, 0}},
                   {{2, 0}, {1, 0}, {0, 0}, {0, 1}},
               }) {}

  void ReBase(){
    if(_currState == 0){_currPos-=Point<float>{1,0};}
    if(_currState == 2){_currPos+=Point<float>{1,0};}
  };
};

/*
(0)     (1)     (2)     (3)
X 0 0   0 0 0   0 X 0   X X 0
X X 0   0 X X   0 X X   0 X X
0 X 0   X X 0   0 0 X   0 0 0
*/
class STetrom : public Tetrom {
public:
  STetrom(Point<int> initPos, int initState)
      : Tetrom(initPos, initState, TetromType::S,
               {
                   {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
                   {{0, 2}, {1, 2}, {1, 1}, {2, 1}},
                   {{2, 2}, {2, 1}, {1, 1}, {1, 0}},
                   {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
               }) {}
  
  void ReBase(){
    if(_currState == 0){_currPos-=Point<float>{1,0};}
    if(_currState == 2){_currPos+=Point<float>{1,0};}
  };
};

/*
(0)     (1)     (2)     (3)
0 0 0   X 0 0   0 X 0   0 0 x
X X X   X X 0   X X X   0 X X
0 X 0   X 0 0   0 0 0   0 0 x
*/
class TTetrom : public Tetrom {
public:
  TTetrom(Point<int> initPos, int initState)
      : Tetrom(initPos, initState, TetromType::T,
               {
                   {{0, 1}, {1, 1}, {2, 1}, {1, 2}},
                   {{0, 0}, {0, 1}, {0, 2}, {1, 1}},
                   {{0, 1}, {1, 1}, {2, 1}, {1, 0}},
                   {{2, 0}, {2, 1}, {2, 2}, {1, 1}},
               }) {}
  
  void ReBase(){
    if(_currState == 1){_currPos-=Point<float>{1,0};}
    if(_currState == 3){_currPos+=Point<float>{1,0};}
  };
};

/*
(0)
X X
X X
*/
class OTetrom : public Tetrom {
public:
  OTetrom(Point<int> initPos, int initState)
      : Tetrom(initPos, initState, TetromType::O,
               {
                   {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
               }) {}
  void ReBase(){};
};

/*
(0)       (1)
X 0 0 0   X X X X
X 0 0 0   0 0 0 0
X 0 0 0   0 0 0 0
X 0 0 0   0 0 0 0
*/
class ITetrom : public Tetrom {
public:
  ITetrom(Point<int> initPos, int initState)
      : Tetrom(initPos, initState, TetromType::I,
               {
                   {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
                   {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
               }) {}
  
  void ReBase()
  {
    if(_currState == 0){_currPos-=Point<float>{3,0};}
  };
};

#endif // __TETROM_H__