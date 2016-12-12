#include <iostream>
#include <fstream>
#include <string>

#ifndef NODE_CPP
    #define NODE_CPP
    #include "Node.cpp"
#endif

#ifndef QUADTREE
    #define QUADTREE
    #include "QuadTree.h"
#endif

using namespace std;

/**
 * Initialize the QuadTree with the given width and height
 * The bounds of a QuadTree are indicated by {x-(x+width)] in the x-direction, and by {y-(y+height)] in the y-direction
 * width - the width of the QuadTree
 * height - the height of the QuadTree
 */
template <class Object>
QuadTree<Object>::QuadTree(unsigned width, unsigned height) {
    this->width = width;
    this->height = height;
    this->x = 0; // set the default x-offset to 0
    this->y = 0; // set the default y-offset to 0
    this->level = 0; // set the default level to 0
}

/**
 * Initialize the QuadTree with the given width, height and level
 * width - the width of the QuadTree
 * height - the height of the QuadTree
 * level - the level, or depth of the QuadTree
 */
template <class Object>
QuadTree<Object>::QuadTree(unsigned width, unsigned height, unsigned level) {
    this->width = width;
    this->height = height;
    this->x = 0;
    this->y = 0;
    this->level = level;
}

/**
 * Initialize the QuadTree with the given width, height, x-offset, y-offset and level
 * width - the width of the QuadTree
 * height - the height of the QuadTree
 * x - the x-offset, or the base, of the QuadTree
 * y - the y-offset, or the base, of the QuadTree
 * level - the level, or depth of the QuadTree
 */
template <class Object>
QuadTree<Object>::QuadTree(unsigned width, unsigned height, unsigned x, unsigned y, unsigned level) {
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->level = level;
}

/**
 * Insert the given element into the QuadTree
 * element - the element to be inserted into the QuadTree
 */
template <class Object>
void QuadTree<Object>::insert(Node<Object> * element) {
    if (element->getX() >= (this->x + this->width) || element->getY() >= (this->y + this->height) || element->getX() < 0 || element->getY() < 0) { // if the input is out of bounds
        cout << this->x << "-" << this->width << "-" << this->y << "-" << this->height << endl;
        cout << element->getX() << "; " << element->getY() << endl;
        throw CoordinateOutOfBoundsException(element->getX(), element->getY()); // throw an exception that indicates this
    } else if (!this->intermediate && !this->hasChild) { // if this QuadTree is not an intermediate and does not have a child element
        this->values.push_back(element); // insert the new value into the QuadTree
        this->hasChild = true; // update the flag to indicate that the QuadTree now has a child
    } else if (!this->intermediate && this->hasChild) { // if this QuadTree does not have QuadTree instances, but has a child element
        Node<Object> * front = ((Node<Object> *)(this->values.front())); // fetch the first child Node of this QuadTree
        if (front->getValue() == element->getValue()) { // if the new Node has the same value
            this->values.push_back(element); // add it to the list of Node children, all of which should have the same value
        } else if (this->width > 1 && this->height > 1) { // else, if this QuadTree can be further split into four other QuadTrees
            this->intermediate = true; // make this an intermediate QuadTree - a QuadTree that is split into four QuadTrees
            this->hasChild = false; // remove the flag indicating that the QuadTree has a child element
            
            this->children[0] = new QuadTree(this->width/2, this->height/2, this->x, this->y, this->level + 1); // initialize the NW child
            this->children[1] = new QuadTree(this->width - this->width/2, this->height/2, this->x + this->width/2, this->y, this->level + 1); // initialize the NE child
            this->children[2] = new QuadTree(this->width/2, this->height - this->height/2, this->x, this->y + this->height/2, this->level + 1); // initialize the SW child
            this->children[3] = new QuadTree(this->width - this->width/2, this->height - this->height/2, this->x + this->width/2, this->y + this->height/2, this->level + 1); // initialize the SE child
            
            for (unsigned i = 0; i < this->values.size(); i++) { // for each child Node
                this->insert(this->values.at(i)); // insert the element that was already linked to this QuadTree into this QuadTree - since the QuadTree has now been split, this value will be inserted into one of its children
            }
            this->insert(element);
            this->values.clear(); // remove all the child Node instances
        } else {
            this->values.push_back(element); // add it to the list of Node children
        }
    } else if (this->intermediate) { // if this is an intermediate QuadTree - a QuadTree that is split into four QuadTrees
        // check to which QuadTree the given element should be added
        if (element->getX() < (this->x + this->width/2) && element->getY() < (this->y + this->height/2)) { // if the given element belongs to the NW QuadTree
            this->children[0]->insert(element); // insert the element into the NW QuadTree
        } else if (element->getX() >= (this->x + this->width/2) && element->getY() < (this->y + this->height/2)) { // if the given element belongs to the NE QuadTree
            this->children[1]->insert(element); // insert the element into the NE QuadTree
        } else if (element->getX() < (this->x + this->width/2) && element->getY() >= (this->y + this->height/2)) { // if the given element belongs to the SW QuadTree
            this->children[2]->insert(element); // insert the element into the SW QuadTree
        } else if (element->getX() >= (this->x + this->width/2) && element->getY() >= (this->y + this->height/2)) { // if the given element belongs to the SE QuadTree
            this->children[3]->insert(element); // insert the element into the SE QuadTree
        }
    }
}

/**
 * Get the value of the element at the given coordinates
 * x - the x-coordinate of the desired value
 * y - the y-coordinate of the desired value
 * return - the value of the element at the given coordinates
 */
template <class Object>
Object QuadTree<Object>::get(unsigned x, unsigned y) {
    if (x > (this->x + this->width) || y > (this->y + this->height) || x < 0 || y < 0) { // if the input is out of bounds
        throw CoordinateOutOfBoundsException(x, y); // throw an exception indicating this
    } else if (this->intermediate) { // if this is an intermediate QuadTree - a QuadTree that is split into four QuadTrees
        if (x < (this->x + this->width/2) && y < (this->y + this->height/2)) { // if the coordinate belongs to the NW QuadTree
            return this->children[0]->get(x, y); // search for the value in the NW QuadTree
        } else if (x >= (this->x + this->width/2) && y < (this->y + this->height/2)) { // if the coordinate belongs to the NE QuadTree
            return this->children[1]->get(x, y); // search for the value in the NE QuadTree
        } else if (x < (this->x + this->width/2) && y >= (this->y + this->height/2)) { // if the coordinate belongs to the SW QuadTree
            return this->children[2]->get(x, y); // search for the value in the SW QuadTree
        } else if (x >= (this->x + this->width/2) && y >= (this->y + this->height/2)) { // if the coordinate belongs to the SE QuadTree
            return this->children[3]->get(x, y); // search for the value in the SE QuadTree
        }
    } else if (!this->intermediate && this->hasChild) { // else, if this is a leaf
        for (unsigned i = 0; i < this->values.size(); i++) { // for each child Node
            Node<Object> * node = this->values.at(i); // get the Node at index i
            if (node->getX() == x && node->getY() == y) { // if the coordinates of the Node are the same as the given coordinates
                return node->getValue(); // return the value
            }
        }
    } else { // else, it means that this is either an intermediate QuadTree - a QuadTree that is split into four QuadTrees - or it is a leaf, but either it does not have a child, or its coordinates are not the same as the given coordinates
        throw CoordinateUnboundException(x, y); // throw an exception indicating this
    }
    return Object();
}

/**
 * Save the QuadTree to a file with the given name
 * name - the name of the file where the QuadTree will be saved
 */
template <class Object>
void QuadTree<Object>::save(string name) {
    ofstream file(name + ".4", ios::binary); // open or create the file
    file.write((char *)&this->width, sizeof(this->width)); // write to the file the width of the QuadTree
    file.write((char *)&this->height, sizeof(this->height)); // write to the file the height of the QuadTree
    for (unsigned x = 0; x < this->width; x++) { // for each row in the QuadTree
        for (unsigned y = 0; y < this->height; y++) { // for each column in the QuadTree
            file.write((char *)&x, sizeof(x)); // write to the file the x-coordinate
            file.write((char *)&y, sizeof(y)); // write to the file the y-coordinate
            Object object = this->get(x, y); // retrieve the Object at the given coordinates
            file.write((char *)&object, sizeof(object)); // write to the file the Object
        }
    }
    file.close(); // close the file
}

/**
 * Set the width of the QuadTree to the given one
 * width - the new width of the QuadTree
 */
template <class Object>
void QuadTree<Object>::setWidth(unsigned width) {
    this->width = width;
}

/**
 * Get the width of the QuadTree
 * width - the width of the QuadTree
 */
template <class Object>
unsigned QuadTree<Object>::getWidth() {
    return this->width;
}

/**
 * Set the height of the QuadTree to the given one
 * height - the new height of the QuadTree
 */
template <class Object>
void QuadTree<Object>::setHeight(unsigned height) {
    this->height = height;
}

/**
 * Get the height of the QuadTree
 * height - the height of the QuadTree
 */
template <class Object>
unsigned QuadTree<Object>::getHeight() {
    return this->height;
}

/**
 * Set the x-offset of the QuadTree to the given one
 * x - the new x-offset of the QuadTree
 */
template <class Object>
void QuadTree<Object>::setX(unsigned x) {
    this->x = x;
}

/**
 * Get the x-offset of the QuadTree
 * x - the x-offset of the QuadTree
 */
template <class Object>
unsigned QuadTree<Object>::getX() {
    return this->x;
}

/**
 * Set the y-offset of the QuadTree to the given one
 * y - the new y-offset of the QuadTree
 */
template <class Object>
void QuadTree<Object>::setY(unsigned y) {
    this->y = y;
}

/**
 * Get the y-offset of the QuadTree
 * y - the y-offset of the QuadTree
 */
template <class Object>
unsigned QuadTree<Object>::getY() {
    return this->y;
}

/**
 * Set the level, or depth, of the QuadTree to the given one
 * level - the new level, or depth, of the QuadTree
 */
template <class Object>
void QuadTree<Object>::setLevel(unsigned level) {
    this->level = level;
}

/**
 * Get the level, or depth, of the QuadTree
 * level - the level, or depth, of the QuadTree
 */
template <class Object>
unsigned QuadTree<Object>::getLevel() {
    return this->level;
}

/**
 * Print the QuadTree
 */
template <class Object>
void QuadTree<Object>::print() {
    string s = "";
    for (unsigned i = 0; i < this->level; i++) {
        s += "\t"; // use indentation to represent levels
    }
    cout << endl;
    if (this->intermediate || this->hasChild) { // if this is an intermediate QuadTree - a QuadTree that is split into four QuadTrees - or it has a child, then it can be printed  
        if (!this->intermediate && this->hasChild) {
            //cout << s << "(" << this->x << ", " << this->y << "); (" << this->width << ", " << this->height << "): ";
            cout << s;
            this->values.front()->print();
        } else if (this->intermediate) {
            cout << s << "Mixed";
            this->children[0]->print(); // print the NW QuadTree
            this->children[1]->print(); // print the NE QuadTree
            this->children[2]->print(); // print the SW QuadTree
            this->children[3]->print(); // print the SE QuadTree
        }
    }
}
