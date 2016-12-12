#include <iostream>

#ifndef COLOR
    #define COLOR
    #include "Color.h"
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

Color::Color() {}

/**
 * Initialize the Color with the given RGB values
 * red - the R value of the Color
 * green - the G value of the Color
 * blue - the B value of the Color
 */
Color::Color(string red, string green, string blue) {
    this->setRed(red);
    this->setGreen(green);
    this->setBlue(blue);
}

/**
 * Set the new R value of the Color
 * red - the R value of the Color
 */
void Color::setRed(string red) {
    try {
        this->validate(red);
        this->red = red;
        this->updateValue();
    } catch (InvalidInputException e) {
        cout << e.getMessage() << endl;
    }
}

/**
 * Set the new G value of the Color
 * green - the G value of the Color
 */
void Color::setGreen(string green) {
    try {
        this->validate(green);
        this->green = green;
        this->updateValue();
    } catch (InvalidInputException e) {
        cout << e.getMessage() << endl;
    }
}

/**
 * Set the new B value of the Color
 * blue - the B value of the Color
 */
void Color::setBlue(string blue) {    
    try {
        this->validate(blue);
        this->blue = blue;
        this->updateValue();
    } catch (InvalidInputException e) {
        cout << e.getMessage() << endl;
    }
}

/**
 * Get the R value of the Color
 * return - the R value of the Color
 */
string Color::getRed() {
    return this->red;
}

/**
 * Get the G value of the Color
 * return - the G value of the Color
 */
string Color::getGreen() {
    return this->green;
}

/**
 * Get the B value of the Color
 * return - the B value of the Color
 */
string Color::getBlue() {
    return this->blue;
}

/**
 * Set the new value of the Color to the given one
 * value - the new value of the Color
 */
void Color::setValue(string value) {
    try {
        this->validate(value);
        this->value = value;
    } catch (InvalidInputException e) {
        cout << e.getMessage() << endl;
    }
}

/**
 * Update the value of the Color
 */
void Color::updateValue() {
    this->value = this->red + this->green + this->blue;
}

/**
 * Get the hex representation of the color
 * return - the hex representation of the color
 */
string Color::getValue() const {
    return this->red + this->green + this->blue;
}

/**
 * Check whether the given Color is the same as the current one
 * return - a boolean indicating whether the given Color is the same as the current one (true) or not (false)
 */
bool Color::operator== (const Color &color) const {
    return (this->getValue().compare(color.getValue()) == 0); // if the comparison function returns 0, then the two Colors are identical
}

void Color::validate(string s) {
    locale loc;
    for (unsigned i = 0; i < s.length(); i++) {
        char c = tolower(s[i], loc);
        if (!(c >= '0' && c <= '9') && !(c >= 'a' && c <= 'f')) {
            throw InvalidInputException(s[i]);
        }
    }
}

/**
 * Print the hex representation of the color
 */
void Color::print() {
    if (this->value.compare("ff0000") == 0) {
        cout << "RED" << endl;
    } else if (this->value.compare("00ff00") == 0) {
        cout << "GREEN" << endl;
    } else if (this->value.compare("0000ff") == 0) {
        cout << "BLUE" << endl;
    } else if (this->value.compare("000000") == 0) {
        cout << "BLACK" << endl;
    } else if (this->value.compare("ffffff") == 0) {
        cout << "WHITE" << endl;
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
QuadTree<Color> * Color::parse(unsigned lines, unsigned characters,  ifstream &file) {
    QuadTree<Color> * quadtree = new QuadTree<Color>(characters/6, lines); // initialize the QuadTree<Object> with dimensions (line length x number of lines)
    for (unsigned l = 0; l < lines; l++) { // for each line
        string line;
        getline(file, line); // read the line
        for (unsigned c = 0; c < characters/6; c++) { // for each set of six characters, indicating a hex representation of a color
            Color color = Color();
            color.setRed(line.substr(c * 6 + 0, 2)); // extract the R value
            color.setGreen(line.substr(c * 6 + 2, 2)); // extract the G value
            color.setBlue(line.substr(c * 6 + 4, 2)); // extract the B value
            quadtree->insert(new Node<Color>(c, l, color)); // insert the Color into the QuadTree
        }
    }
    return quadtree;
}

/**
 * Parse the given line and convert its value into a Color instance
 * line - the line to parse
 * return - the Color instance as parsed from the line
 */
Color Color::parseLine(string line) {
    string value = line.substr(line.find_last_of(File<Boolean>::DELIMETER) + 1);
    string r = value.substr(0, 2);
    string g = value.substr(2, 2);
    string b = value.substr(4, 2);
    //TODO: Check for exception
    return Color(r, g, b);
}
