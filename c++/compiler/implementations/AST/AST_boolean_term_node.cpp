//
// Created by memonick on 13/04/2016.
//

#include "../../headers/AST/AST_boolean_term_node.h"

/**
 * Initialize the boolean  node with the given level and value
 * level            the level of the boolean  node
 * value            the value of the boolean  node
 */
AST_boolean_term_node::AST_boolean_term_node(unsigned level, string value) : AST_term_node(level, value), AST_binary_expression_node(level, value) {}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_boolean_term_node::accept(visitor * v) {
    v->visit(this);
}
