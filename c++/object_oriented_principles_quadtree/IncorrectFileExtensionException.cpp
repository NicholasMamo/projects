#include <iostream>
#include <string>

#include "IncorrectFileExtensionException.h"

using namespace std;

/**
 * An exception that indicates that the given extension is not of the required type
 * extension - the incorrect extension
 */
IncorrectFileExtensionException::IncorrectFileExtensionException(string extension) {
    this->message = "Extension ";
    this->message += extension;
    this->message += " is not allowed!";
}
