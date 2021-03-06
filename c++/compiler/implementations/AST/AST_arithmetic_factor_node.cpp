//
// Created by memonick on 13/04/2016.
//

#include "../../headers/AST/AST_arithmetic_factor_node.h"

/**
 * Initialize the arithmetic factor node with the given level and value
 * level            the level of the arithmetic factor node
 * value            the value of the arithmetic factor node
 */
AST_arithmetic_factor_node::AST_arithmetic_factor_node(unsigned level, string value) : AST_factor_node(level, value), AST_binary_expression_node(level, value) {}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_arithmetic_factor_node::accept(visitor * v) {
    v->visit(this);
}
