#include <iostream>
#include <string>

#include "CoordinateUnboundException.h"

using namespace std;

/**
 * An exception that indicates that the given coordinate in the QuadTree is not bound (it does not have a value)
 * The constructor initializes the return message with the given coordinates
 * x - the x-coordinate
 * y - the y-coordinate
 */
CoordinateUnboundException::CoordinateUnboundException(unsigned x, unsigned y) {
    this->message = "Coordinate (";
    this->message += to_string(x);
    this->message += ", ";
    this->message += to_string(y);
    this->message += ") is not bound!";
}
