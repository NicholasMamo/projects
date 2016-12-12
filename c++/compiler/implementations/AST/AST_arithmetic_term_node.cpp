//
// Created by memonick on 13/04/2016.
//

#include "../../headers/AST/AST_arithmetic_term_node.h"

/**
 * Initialize the arithmetic term node with the given level and value
 * level            the level of the arithmetic term node
 * value            the value of the arithmetic term node
 */
AST_arithmetic_term_node::AST_arithmetic_term_node(unsigned level, string value) : AST_term_node(level, value), AST_binary_expression_node(level, value) {}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_arithmetic_term_node::accept(visitor * v) {
    v->visit(this);
}
