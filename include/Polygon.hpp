#ifndef POLYGON_H
#define POLYGON_H

#include <string>
#include "Shape.hpp"

class Polygon : public Shape {

public:
  Polygon(Coordinate *coords, int coordsSize);
  std::string getType();
  float area();
  float circumference();
  float position();
  bool isConvex();
  float distance(Polygon s);

};

#endif
