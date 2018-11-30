#ifndef SHAPE_H
#define SHAPE_H

#include "Coordinate.hpp"
#include <string>

class Shape {
 protected:
  Coordinate *coordsArr;
  int pointCount;
  std::string typeOfShape;

 public:
  virtual std::string getType() = 0;
  float area();
  float circumference();
  float position();
  bool isConvex();
  // float distance(Shape s);
};

#endif
