//
// Created by memonick on 10/04/2016.
//

#include "../../headers/AST/AST_factor_node.h"

/**
 * Initialize the factor node with the given level and value
 * level            the level of the factor node
 * value            the value of the factor node
 */
AST_factor_node::AST_factor_node(unsigned level, string value) : AST_binary_expression_node(level, value) {}