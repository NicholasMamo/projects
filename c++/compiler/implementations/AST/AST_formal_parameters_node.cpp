//
// Created by memonick on 12/04/2016.
//

#include "../../headers/AST/AST_formal_parameters_node.h"

/**
 * Create the node with the given level and value
 * level            the level of the node
 */
AST_formal_parameters_node::AST_formal_parameters_node(unsigned level) {
    this->set_level(level);
}

/**
 * Delete the node
 */
AST_formal_parameters_node::~AST_formal_parameters_node() {
    for (unsigned i = 0; i < this->formal_parameters.size(); i++) {
        delete this->formal_parameters.at(i);
    }
}

/**
 * Add a formal parameter
 * formal_parameter the formal parameter to add
 */
void AST_formal_parameters_node::add_formal_parameter(AST_formal_parameter_node * formal_parameter) {
    formal_parameter->set_level(this->level + 1);
    this->formal_parameters.push_back(formal_parameter);
}

/**
 * Get the list of formal parameters
 * return           the list of formal parameters
 */
vector<AST_formal_parameter_node *> AST_formal_parameters_node::get_formal_parameters() {
    return this->formal_parameters;
}

/**
 * Set the level of the node, and any children it may have, to the one given
 * level            the new level of the node
 */
void AST_formal_parameters_node::set_level(unsigned level) {
    this->level = level;
    for (unsigned i = 0; i < this->formal_parameters.size(); i++) {
        this->formal_parameters.at(i)->set_level(level + 1);
    }
}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_formal_parameters_node::accept(visitor * v) {
    v->visit(this);
}
