#include <iostream>

#ifndef BOOLEAN
    #define BOOLEAN
    #include "Boolean.h"
#endif

#ifndef FILE_CPP
    #define FILE_CPP
    #include "File.cpp"
#endif

#ifndef NODE_CPP
    #define NODE_CPP
    #include "Node.cpp"
#endif

#ifndef QUADTREE_CPP
    #define QUADTREE_CPP
    #include "QuadTree.cpp"
#endif

using namespace std;
using namespace color;

Boolean::Boolean() {}

/**
 * Initialize the Boolean with the given value
 * value - the boolean value of the Boolean
 */
Boolean::Boolean(string value) {
    this->setValue(value);
}

/**
 * Set the new value of the Boolean to the given one
 * value - the new value of the Boolean
 */
void Boolean::setValue(string value) {
    try {
        this->validate(value);
        this->value = value[0];
    } catch (IncorrectInputException e) {
        cout << e.getMessage();
    }
}

void Boolean::validate(string value) {
    char character = value[0];
    if (!(character == 'T' || character == 'F' || character == '\n')) { // if the character is not T, F or a newline character
        throw IncorrectInputException(character); // then the character is not acceptable, so throw an exception that indicates this
    }
}

/**
 * Get the boolean value of the Boolean
 * return - a boolean indicating whether the Boolean represents a T tile (true) or a F tile (false) 
 */
bool Boolean::getBoolean() const {
    if (this->value.compare("T") == 0) {
        return true;
    } else {
        return false;
    }
}

/**
 * Get the value of the Boolean
 * return - the textual representation of the Boolean
 */
string Boolean::getValue() const {
    return this->value;
}

/**
 * Check whether the given Boolean is the same as the current one
 * return - a boolean indicating whether the given Boolean is the same as the current one (true) or not (false)
 */
bool Boolean::operator== (const Boolean &boolean) const {
    return (boolean.getValue() == this->value);
}

/**
 * Print the Boolean
 */
void Boolean::print() {
    if (this->getBoolean()) {
        cout << "WHITE" << endl;
    } else {
        cout << "BLACK" << endl;
    }
}

/**
 * Parse the given file and construct a QuadTree representation of it
 * lines - the number of lines in the file
 * characters - the number of characters in each line
 * file - the file containing the image
 * return - a QuadTree representation of the given file
 */
QuadTree<Boolean> * Boolean::parse(unsigned lines, unsigned characters, ifstream &file) {
    QuadTree<Boolean> * quadtree = new QuadTree<Boolean>(characters, lines); // initialize the QuadTree<Object> with dimensions (line length x number of lines)
    for (unsigned l = 0; l < lines; l++) { // for each line
        for (unsigned c = 0; c < characters + 1; c++) { // for each character (including the newline character)
            char character;
            file.get(character); // read the character
            if (character != '\n') {
                Boolean boolean;
                boolean.setValue(string(1, character));
                quadtree->insert(new Node<Boolean>(c, l, boolean)); // add an Node at the coordinate (character, line) to the QuadTree
            }
        }
    }
    return quadtree;
}

/**
 * Parse the given line and convert its value into a Boolean instance
 * line - the line to parse
 * return - the Boolean instance as parsed from the line
 */
Boolean Boolean::parseLine(string line) {
    string value = line.substr(line.find_last_of(File<Boolean>::DELIMETER) + 1);
    return Boolean(value);
}
