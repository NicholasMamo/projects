//
// Created by memonick on 10/04/2016.
//

#ifndef LEXER_AST_FACTOR_NODE_H
#define LEXER_AST_FACTOR_NODE_H

class AST_binary_expression_node;
class visitor;
#include "AST_binary_expression_node.h"

class AST_factor_node : public virtual AST_binary_expression_node {

    public:
        AST_factor_node(unsigned level, string value);

        virtual void accept(visitor * v) = 0;

};

#endif //LEXER_AST_FACTOR_NODE_H
