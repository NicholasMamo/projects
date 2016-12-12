#include <fstream>
#include <iostream>
#include <string>

#ifndef BOOLEAN
    #define BOOLEAN
    #include "Boolean.h"
#endif

#ifndef COORDINATEUNBOUND
    #define COORDINATEUNBOUND
    #include "CoordinateUnboundException.h"
#endif

#ifndef FILE
    #define FILE
    #include "File.h"
#endif

#ifndef QUADTREE
    #define QUADTREE
    #include "QuadTree<Object>.h"
#endif

using namespace std;

template <class Object>
const string File<Object>::DELIMETER = string("|"); // the DELIMETER variable is used to separate coordinates and values when saving and loading files

/**
 * Load the file with the given filename if it exists and is of the correct format
 * filename - the name of the file to be loaded
 */
template <class Object>
File<Object>::File(string filename) {
    string extension = filename.substr(filename.find_last_of(".") + 1); // get the file's extension
    if (extension == "txt") { // if the extension is correct
        if (ifstream(filename)) { // and the file exists
            this->file.open(filename); // load the file with the given filename into memory
        } else { // if the file does not exist
            throw FileNotFoundException(filename); // throw an exception that indicates that the file was not found
        }
    } else { // if the extension is incorrect
        throw IncorrectFileExtensionException(extension); // throw an exception that indicates that the file extension is incorrect
    }
}

/**
 * When deleting the File instance, close the associated file
 */
template <class Object>
File<Object>::~File() {
    this->file.close();
}

/**
 * Parse the loaded file and construct a QuadTree representing its contents
 * return - the QuadTree<Object> construction of the file
 */
template <class Object>
QuadTree<Object> * File<Object>::getQuadTree() {
    unsigned lines = this->getLines(); // get the number of lines in the file
    unsigned lineLength = this->getLineLength(); // get the length of each line in the file
    this->file.clear(); // clear the file's flags
    this->file.seekg(0); // reset the position of the read pointer    
    return Object::parse(lines, lineLength, this->file);
}

/**
 * Save the given QuadTree<Object> to a file with the given filename
 * quadtree - a reference to the QuadTree<Object> to be saved
 * filename - the desired filename
 */
template <class Object>
void File<Object>::save(QuadTree<Object> &quadtree, string filename) {
    if (filename.find_last_of('.') == string::npos) { // if no extension is given
        filename += ".4"; // append the extension
    } else if (filename.substr(filename.find_last_of(".") + 1).compare("4") != 0) { // if the extension is incorrect
        throw IncorrectFileExtensionException(filename.substr(filename.find_last_of(".") + 1)); // throw an exception that indicates that the extension is incorrect
    }
    
    ofstream file;
    file.open(filename, ios::out); // create the file if it doesn't exist
    unsigned width = quadtree.getWidth();
    unsigned height = quadtree.getHeight();
    file << width << endl;
    file << height << endl;
    for (unsigned x = 0; x < width; x++) { // traverse each row in the QuadTree<Object>
        for (unsigned y = 0; y < height; y++) { // traverse each column in the QuadTree<Object>
            try {
                file << x << File<Object>::DELIMETER << y << File<Object>::DELIMETER << (quadtree.get(x, y).getValue()) << endl; // write the textual value of the Object to the file at the given coordinate
            } catch (CoordinateUnboundException e) {
                cout << e.getMessage() << endl; // if there is nothing in that coordinate, display an error message
            }
        }
    }
    file.close(); // close the output file
}

/**
 * Load the QuadTree stored in the file with the given name
 * name - the name of the file where the QuadTree will be retrieved from
 * return - a pointer to the QuadTree loaded from the file having the given name
 */
template <class Object>
QuadTree<Object> * File<Object>::load(string filename) {
    if (filename.find_last_of('.') == string::npos) { // if no extension is given
        filename += ".4"; // append the extension
    } else if (filename.substr(filename.find_last_of(".") + 1).compare("4") != 0) { // if the extension is incorrect
        throw IncorrectFileExtensionException(filename.substr(filename.find_last_of(".") + 1)); // throw an exception that indicates that the extension is incorrect
    }
    
    ifstream file;
    file.open(filename, ios::in); // create the file if it doesn't exist
    
    if (file.is_open()) {
        unsigned width = 0, height = 0;
        string widthString, heightString;
        getline(file, widthString);
        getline(file, heightString);
        width = stoi(widthString);
        height = stoi(heightString);
        
        QuadTree<Object> * quadtree = new QuadTree<Object>(width, height); // initialize the QuadTree with the width and height retrieved from the file
        for (unsigned i = 0; i < width * height; i++) { // for each row and column in the QuadTree
            unsigned x, y;
            string line;
            getline(file, line);
            x = stoi(line.substr(0, line.find(File<Object>::DELIMETER)));
            y = stoi(line.substr(line.find(File<Object>::DELIMETER) + 1, line.find_last_of(File<Object>::DELIMETER)));
            Object object = Object::parseLine(line);
            Node<Object> * node = new Node<Object>(x, y, object); // create the Node with the given coordinates and Object
            quadtree->insert(node); // insert the Node into the QuadTree
        }
        file.close(); // close the file
        return quadtree;
    } else {
        throw FileNotFoundException(filename);
    }
}

/**
 * Print the file's contents
 */
template <class Object>
void File<Object>::print() {
    this->file.clear(); // clear the file's flags
    this->file.seekg(0); // reset the position of the read pointer
    string line;
    while (!getline(this->file, line).eof()) { // while there is something left in the file
        if (line.length() > 0) {
            cout << line << endl; // output the line if its length is more than 0
        }
    }
}

/**
 * Get the length of each line in the file
 * return - the length of each line in the file
 */
template <class Object>
unsigned File<Object>::getLineLength() {
    this->file.clear(); // clear the file's flags
    this->file.seekg(0); // reset the position of the read pointer
    string line;
    getline(this->file, line); // get the first line in the file
    return line.length();
}

/**
 * Get the number of lines in the file
 * return - the number of lines in the file
 */
template <class Object>
unsigned File<Object>::getLines() {
    this->file.clear(); // clear the file's flags
    this->file.seekg(0); // reset the position of the read pointer
    unsigned lines = 0;
    string line;
    while (!getline(this->file, line).eof()) { // while there is something left in the file
        lines++; // increment the counter indicating the number of lines in the file
    }
    return lines;
}
