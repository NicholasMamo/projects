//
// Created by memonick on 15/03/2016.
//

#include <iostream>

#include "../../headers/AST/AST_binary_expression_node.h"

using namespace std;

/**
 * Create the node with the given level and value
 * level            the level of the node
 * value            the value of the node
 */
AST_binary_expression_node::AST_binary_expression_node(unsigned level, string value) {
    this->set_level(level);
    this->set_value(value);
    this->left_child = NULL;
    this->right_child = NULL;
}

/**
 * Delete the node
 */
AST_binary_expression_node::~AST_binary_expression_node() {
    delete this->left_child;
    delete this->right_child;
}

/**
 * Set the value of the node to the one provided
 * value            the new value of the node
 */
void AST_binary_expression_node::set_value(string value) {
    this->value = value;
}

/**
 * Set the left child of the node to the one provided
 * left_child       the new left child of the node
 */
void AST_binary_expression_node::set_left_child(AST_node * left_child) {
    this->left_child = left_child;
    this->left_child->set_level(this->level + 1);
    this->has_left_child = true;
}

/**
 * Set the right child of the node to the one provided
 * right_child       the new right child of the node
 */
void AST_binary_expression_node::set_right_child(AST_node * right_child) {
    this->right_child = right_child;
    this->right_child->set_level(this->level + 1);
    this->has_right_child = true;
}

/**
 * Get the value of the node
 * return           the value of the node
 */
string AST_binary_expression_node::get_value() {
    return this->value;
}

/**
 * Get a boolean indicating whether this node has a left child (true), or not (false)
 * return           a boolean indicating whether this node has a left child (true), or not (false)
 */
bool AST_binary_expression_node::contains_left_child() {
    return this->has_left_child;
}

/**
 * Get a boolean indicating whether this node has a right child (true), or not (false)
 * return           a boolean indicating whether this node has a right child (true), or not (false)
 */
bool AST_binary_expression_node::contains_right_child() {
    return this->has_right_child;
}

/**
 * Get the left child of the node
 * return           the left child of the node
 */
AST_node * AST_binary_expression_node::get_left_child() {
    return this->left_child;
}

/**
 * Get the right child of the node
 * return           the right child of the node
 */
AST_node * AST_binary_expression_node::get_right_child() {
    return this->right_child;
}

/**
 * Set the level of the node, recursively changing the level of its children
 * level            the new level of the node
 */
void AST_binary_expression_node::set_level(unsigned level) {
    this->level = level;
    if (this->has_left_child) {
        this->left_child->set_level(level + 1);
    }
    if (this->has_right_child) {
        this->right_child->set_level(level + 1);
    }
}
