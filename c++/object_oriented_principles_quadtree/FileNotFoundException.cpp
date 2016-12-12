#include <iostream>
#include <string>

#include "FileNotFoundException.h"

using namespace std;

/**
 * An exception that indicates that the file with the given filename was not found
 * filename - the filename of the file that was not found
 */
FileNotFoundException::FileNotFoundException(string filename) {
    this->message = filename;
    this->message += " was not found!";
}
