#ifndef __POINT_H__
#define __POINT_H__

struct Intersection
{
    bool Down;
    bool Left;
    bool Right;

    bool operator==(const Intersection &a) const { 
        return ((Down == a.Down) && (Left == a.Left) && (a.Right == a.Right)); 
    }
    Intersection& operator|=(const Intersection &a){
        Down |= a.Down;
        Left |= a.Left;
        Right |= a.Right;
    }

};

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
  Intersection CheckNeighbour(Point p){
    Intersection ret{false, false, false};
    if(((p.y + 1) == y) && (p.x == x)){
        ret.Down = true;
        }
    if(((p.x - 1) == x) && (p.y == y)){
        ret.Left = true;
        }
    if(((p.x + 1) == x) && (p.y == y)){
        ret.Right = true;
        }
    return ret;
  }
};



#endif // __POINT_H__