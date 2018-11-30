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
    distance += coordsArr[i].distance(coordsArr[i+1]);
  }
  return distance;
}

Coordinate Polygon::position() {
  float minX, maxX, minY, maxY;

  for(int i = 0; i < pointCount; i++) {
    double x = coordsArr[i].getX();
    double y = coordsArr[i].getY();
    minX = fmin(minX, x);
    maxX = fmax(maxX, x);
    minY = fmin(minY, y);
    maxY = fmax(maxY, y);    
  }

  float width = maxX - minX;
  float height = maxY - minY;

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
        if (got_negative && got_positive) return false;
    }

    return true;
}

