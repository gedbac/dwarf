#ifndef DWARF_SHARED_POINT_H_
#define DWARF_SHARED_POINT_H_

#include "dwarf.h"

namespace dwarf {

struct Point {
  F32 x;
  F32 y;
  Point() : x(0.0), y(0.0) {}
  Point(F32 x, F32 y) : x(x), y(y) {}
};

}

#endif