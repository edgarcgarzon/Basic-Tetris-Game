#ifndef __POINT_H__
#define __POINT_H__

struct Intersection
{
    bool Down;
    bool Left;
    bool Right;
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
};



#endif // __POINT_H__