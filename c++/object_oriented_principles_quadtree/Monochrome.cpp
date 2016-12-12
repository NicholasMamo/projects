#include <iostream>

#ifndef FILE_CPP
    #define FILE_CPP
    #include "File.cpp"
#endif

#ifndef MONOCHROME
    #define MONOCHROME
    #include "Monochrome.h"
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

Monochrome::Monochrome() {}

/**
 * Initialize the Monochrome with the given value
 * value - the monochromatic value of the Monochrome
 */
Monochrome::Monochrome(string value) {
    this->setValue(value);
}

/**
 * Set the new value of the Monochrome to the given one
 * value - the new value of the Monochrome
 */   
void Monochrome::setValue(string value) {
    try {
        this->validate(value);
        this->value = value;
    } catch (InvalidInputException e) {
        cout << e.getMessage() << endl;
    }
}

/**
 * Get the monochromatic representation of the Monochrome
 * return - the monochromatic representation of the Monochrome
 */
string Monochrome::getValue() const {
    return this->value;
}

/**
 * Check whether the given Monochrome is the same as the current one
 * return - a boolean indicating whether the given Monochrome is the same as the current one (true) or not (false)
 */
bool Monochrome::operator== (const Monochrome &color) const {
    return (this->getValue().compare(color.getValue()) == 0);
}

void Monochrome::validate(string s) {
    locale loc;
    for (unsigned i = 0; i < s.length(); i++) {
        char c = tolower(s[i], loc);
        if (!(c >= '0' && c <= '9') && !(c >= 'a' && c <= 'f')) {
            throw InvalidInputException(s[i]);
        }
    }
}

/**
 * Print the monochromatic representation of the Monochrome
 */ 
void Monochrome::print() {
    if (this->value.compare("ff") == 0) {
        cout << "WHITE" << endl;
    } else if (this->value.compare("00") == 0) {
        cout << "BLACK" << endl;
    } else {
        cout << this->value << endl;
    }
}

/**
 * Parse the given file and construct a QuadTree representation of it
 * lines - the number of lines in the file
 * characters - the number of characters in each line
 * file - the file containing the image
 * return - a QuadTree representation of the given file
 */
QuadTree<Monochrome> * Monochrome::parse(unsigned lines, unsigned characters,  ifstream &file) {
    QuadTree<Monochrome> * quadtree = new QuadTree<Monochrome>(characters/2, lines); // initialize the QuadTree<Object> with dimensions (line length x number of lines)
    for (unsigned l = 0; l < lines; l++) { // for each line
        string line;
        getline(file, line); // read the line
        for (unsigned c = 0; c < characters/2; c++) { // for each set of two characters, indicating a monochromatic representation of a color
            Monochrome monochrome = Monochrome();
            monochrome.setValue(line.substr(c * 2 + 0, 2)); // extract the monochromatic value
            quadtree->insert(new Node<Monochrome>(c, l, monochrome)); // insert the Monochrome into the QuadTree
        }
    }
    return quadtree;
}

/**
 * Parse the given line and convert its value into a Monochrome instance
 * line - the line to parse
 * return - the Monochrome instance as parsed from the line
 */
Monochrome Monochrome::parseLine(string line) {
    string value = line.substr(line.find_last_of(File<Boolean>::DELIMETER) + 1);
    //TODO: Check for exception
    return Monochrome(value);
}
