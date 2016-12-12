#include <iostream>

#ifndef NODE
    #define NODE
    #include "Node.h"
#endif

using namespace std;

template <class Object>
Node<Object>::Node() {}

/**
 * Initialize the Node with the given coordinates and value
 * An Node is comprised of its location and a boolean value
 * x - the x-coordinate of the Node
 * y - the y-coordinate of the Node
 * value - the boolean value of the Node
 */
template <class Object>
Node<Object>::Node(unsigned x, unsigned y, Object value) {
    this->x = x;
    this->y = y;
    this->value = value;
}

/**
 * Set the x-coordinate of the Node to the given x-coordinate
 * x - the new x-coordinate of the Node
 */
template <class Object>
void Node<Object>::setX(unsigned x) {
    this->x = x;
}

/**
 * Get the x-coordinate of the Node
 * return - the x-coordinate of the Node
 */
template <class Object>
unsigned Node<Object>::getX() {
    return this->x;
}

/**
 * Set the y-coordinate of the Node to the given y-coordinate
 * y - the new y-coordinate of the Node
 */
template <class Object>
void Node<Object>::setY(unsigned y) {
    this->y = y;
}

/**
 * Get the y-coordinate of the Node
 * return - the y-coordinate of the Node
 */
template <class Object>
unsigned Node<Object>::getY() {
    return this->y;
}

/**
 * Set the value of the Node to the given one
 * value - the new value of the Node
 */
template <class Object>
void Node<Object>::setValue(Object value) {
    this->value = value;
}

/**
 * Get the value of the Node
 * return - the value of the Node
 */
template <class Object>
Object Node<Object>::getValue() {
    return this->value;
}

/**
 * Print the Node in the format "(x, y): value"
 */
template <class Object>
void Node<Object>::print() {
    //cout << "(" << this->x << ", " << this->y << "): " << (this->value ? "T" : "F") << endl;
    this->value.print();
}
