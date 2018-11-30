#include <iostream>
#include <string>
#include <cmath>
#include "../include/Polygon.hpp"

Polygon::Polygon(Coordinate *coords, int coordSize) {
  pointCount = coordSize;
  coordsArr = new Coordinate[pointCount];
  switch(pointCount){
  case 1:
    typeOfShape = "Point";
    break;
  case 2:
    typeOfShape = "Line";
    break;
  case 3:
    typeOfShape = "Triangle";
    break;
  default:
    typeOfShape = "Polygon";
    break;
  }
  for(int i = 0; i < pointCount; i++) {
    coordsArr[i] = coords[i];
  }
}

std::string Polygon::getType(){
  return typeOfShape;
}

float Polygon::area() {

  if(convexHasBeenRun) {
    if(pointCount < 3 || !convex) {
      return -1;
    }
  }
  else{
    isConvex();
    if(pointCount < 3 || !convex) {
      return -1;
    }
  }

  float area = 0;         // Accumulates area in the loop
  int j = pointCount-1;  // The last vertex is the 'previous' one to the first
  float xPts[pointCount];
  float yPts[pointCount];
  for(int i = 0; i < pointCount; i++) {
    xPts[i] = coordsArr[i].getX();
    yPts[i] = coordsArr[i].getY();
  }

  for (int i=0; i < pointCount; i++){
    area += (xPts[j] + xPts[i]) * (yPts[j] - yPts[i]);
    j = i;  //j is previous vertex to i
  }



  return area/2;
}

float Polygon::circumference() {
  float distance = 0;
  for(int i = 0; i < pointCount; i++) {
    distance += coordsArr[i].distance(coordsArr[(i+1) % pointCount]);
  }
  return distance;
}

Coordinate Polygon::position() {
  float minX = 0, maxX = 0, minY = 0, maxY = 0;
  if(positionHasBeenRun)
    return center;

  for(int i = 0; i < pointCount; i++) {
    double x = coordsArr[i].getX();
    double y = coordsArr[i].getY();
    if(x < minX)
      minX = x;
    if(x > maxX)
      maxX = x;
    if(y < minY)
      minY = y;
    if(y > maxY)
      maxY = y;
  }

  float width = maxX - abs(minX);
  float height = maxY - abs(minY);

  center = {width/2, height/2};
  return center;
}

float CrossProductLength(float Ax, float Ay, float Bx, float By, float Cx, float Cy)
{
  float BAx = Ax - Bx;
  float BAy = Ay - By;
  float BCx = Cx - Bx;
  float BCy = Cy - By;

  return (BAx * BCy - BAy * BCx);
}

bool Polygon::isConvex() {
  if(convexHasBeenRun)
    return convex;

  convexHasBeenRun = true;
  bool got_negative = false;
  bool got_positive = false;
  int B, C;
  for (int A = 0; A < pointCount; A++)
  {
      B = (A + 1) % pointCount;
      C = (B + 1) % pointCount;

      float cross_product = CrossProductLength( coordsArr[A].getX(), coordsArr[A].getY(),
                                                coordsArr[B].getX(), coordsArr[B].getY(),
                                                coordsArr[C].getX(), coordsArr[C].getY());
      if (cross_product < 0)
      {
          got_negative = true;
      }
      else if (cross_product > 0)
      {
          got_positive = true;
      }
      if (got_negative && got_positive){
        convex = false;
        return false; 
      }
  }

  convex = true;
  return true;
}

float Polygon::distance(Polygon s) {
  Coordinate centerS = s.position();
  if(!center.getX())
    position();

  float distance = center.distance(centerS);

  return distance;

};
