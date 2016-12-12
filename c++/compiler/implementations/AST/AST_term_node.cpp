//
// Created by memonick on 10/04/2016.
//

#include "../../headers/AST/AST_term_node.h"

/**
 * Initialize the term node with the given level and value
 * level            the level of the term node
 * value            the value of the term node
 */
AST_term_node::AST_term_node(unsigned level, string value) : AST_binary_expression_node(level, value) {}