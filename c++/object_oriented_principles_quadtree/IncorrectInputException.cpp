#include <iostream>
#include <string>

#include "IncorrectInputException.h"

using namespace std;

/**
 * An exception that indicates that the given character is not acceptable as input
 * c - the character that is not acceptable
 */
IncorrectInputException::IncorrectInputException(char c) {
    this->message = "Character ";
    this->message += c;
    this->message += " is not allowed!";
}
