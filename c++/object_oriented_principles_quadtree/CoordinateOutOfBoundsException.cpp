#include <iostream>
#include <string>

#include "CoordinateOutOfBoundsException.h"

using namespace std;

/**
 * An exception that indicates that the given coordinate is out of bounds
 * The constructor initializes the return message with the given coordinates
 * x - the x-coordinate
 * y - the y-coordinate
 */
CoordinateOutOfBoundsException::CoordinateOutOfBoundsException(unsigned x, unsigned y) {
    // construct the message using the given x- and y-coordinates
    this->message = "Coordinate (";
    this->message += to_string(x);
    this->message += ", ";
    this->message += to_string(y);
    this->message += ") is out of bounds!";
}
