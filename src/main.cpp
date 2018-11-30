#include <iostream>
#include <string>
#include <fstream>
#include "../include/Coordinate.hpp"
#include "../include/Polygon.hpp"

/**
 * Unsure if this library can be used, but I would argue that since it is a
 * string stream it's part of strings. It's necessary for my solution reading
 * the test files line by line and the only thing I'm using from it is the streaming
 * operator (>>).
 */
#include <sstream>

int numberOfBadChars (std::string &str) {
  std::size_t found = str.find_first_not_of("0123456789.- ");
  if (found!=std::string::npos)  {
    return found;
  }
  return 0;
}

void extractFloatsFromString(std::string &str, float *floatArr, int size) {
  std::stringstream ss;

  float tempFloat;
  std::string temp;

  ss << str;

  for(int i = 0; i < size; i++) {
    ss >> temp;
    if(std::stringstream(temp) >> tempFloat) {
      floatArr[i] = tempFloat;
    }
  }
}

int getFloatCount(std::string &str) {
  std::stringstream ss;

  float isFloat;
  int count = 0;
  std::string temp;

  ss << str;
  while(!ss.eof()) {
    ss >> temp;
    if(std::stringstream(temp) >> isFloat) {
      count++;
    }
  }
  return count;
}

int main(int argc, char* argv[]) {
  std::ifstream readFile;
  std::string c;
  int badChars;

  int size;
  int coordSize;
  int line = 0;

  float* floatsFromString;

  Coordinate *coordArr;

  if(argc == 1) {
    std::cout << "Need input file" << std::endl;
  }

  readFile.open(argv[1]);
  if(readFile.bad()) {
    std::cout << "Could not open file" << std::endl;
    exit(EXIT_FAILURE);
  }

  while(std::getline(readFile, c)) {
    badChars = numberOfBadChars(c);
    line++;
    if(badChars) {
      std::cout << "Cannot read file, bad character at line " << line << ", position: " << badChars << std::endl;
      exit(EXIT_FAILURE);
    }
    if(c.length() < 1) {
      std::cout << "Cannot read file, line " << line << " is empty" << badChars << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  readFile.clear();
  readFile.seekg(0, std::ios::beg);

  while(std::getline(readFile, c)){
    size = getFloatCount(c);
    if(size % 2 == 0) {
      coordSize = size/2;
      floatsFromString = new float[size];
      coordArr = new Coordinate[coordSize];
      extractFloatsFromString(c, floatsFromString, size);
      int i = 0;
      while(i < coordSize) {
        for(int j = 0; j < size; j+=2) {
          coordArr[i] = {floatsFromString[j], floatsFromString[j+1]};
          i++;
        }
      }
      Polygon shape(coordArr, coordSize);
      std::cout << "Type of the shape: " << shape.getType() << std::endl;
      std::cout << "Area: " << shape.area() << std::endl;
      std::cout << "Perimeter: " << shape.circumference() << std::endl;
      std::cout << "isConvex: "; shape.isConvex() ? (std::cout << "true" << std::endl) :
      std::cout << "false" << std::endl;
      std::cout << "Position: (" << shape.position().getX() << ", " << shape.position().getY() << ")" << std::endl;

      delete [] coordArr;
    }
  }

  readFile.close();
}
