#ifndef DWARF_SHARED_POINT_H_
#define DWARF_SHARED_POINT_H_

namespace dwarf {

struct Point {
  double x;
  double y;
  Point() : x(0.0), y(0.0) {}
  Point(double x, double y) : x(x), y(y) {}
};

}

#endif