//
// Created by memonick on 13/04/2016.
//

#ifndef LEXER_AST_ARITHMETIC_FACTOR_NODE_H
#define LEXER_AST_ARITHMETIC_FACTOR_NODE_H

class AST_factor_node;
class visitor;

#include "AST_factor_node.h"

class AST_arithmetic_factor_node : public virtual AST_factor_node {

    public:
        AST_arithmetic_factor_node(unsigned level, string value);

        virtual void accept(visitor * v);
};

#include "../visitor/visitor.h"

#endif //LEXER_AST_ARITHMETIC_FACTOR_NODE_H
