#include <iostream>
#include <string>

#ifndef INVALIDINPUT
    #define INVALIDINPUT
    #include "InvalidInputException.h"
#endif

using namespace std;

/**
 * An exception that indicates that the file with the given filename was not found
 * filename - the filename of the file that was not found
 */
InvalidInputException::InvalidInputException(char character) {
    this->message = character;
    this->message += " is not a valid character!";
}
