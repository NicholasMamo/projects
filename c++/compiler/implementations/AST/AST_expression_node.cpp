//
// Created by memonick on 13/04/2016.
//

#include "../../headers/AST/AST_expression_node.h"

/**
 * Initialize the expression node with the given level and value
 * level            the level of the expression node
 * value            the value of the expression node
 */
AST_expression_node::AST_expression_node(unsigned level, string value) : AST_binary_expression_node(level, value) {}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_expression_node::accept(visitor * v) {
    v->visit(this);
}
