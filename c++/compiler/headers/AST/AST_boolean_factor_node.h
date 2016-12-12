//
// Created by memonick on 13/04/2016.
//

#ifndef LEXER_AST_BOOLEAN_FACTOR_NODE_H
#define LEXER_AST_BOOLEAN_FACTOR_NODE_H

class AST_factor_node;

#include "AST_factor_node.h"
#include "../visitor/visitor.h"

class AST_boolean_factor_node : public virtual AST_factor_node {

    public:
        AST_boolean_factor_node(unsigned level, string value);

        virtual void accept(visitor * v);
};

#endif //LEXER_AST_BOOLEAN_FACTOR_NODE_H
