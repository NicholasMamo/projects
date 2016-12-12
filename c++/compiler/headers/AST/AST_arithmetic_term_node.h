//
// Created by memonick on 13/04/2016.
//

#ifndef LEXER_AST_ARITHMETIC_TERM_NODE_H
#define LEXER_AST_ARITHMETIC_TERM_NODE_H

class AST_term_node;
class visitor;

#include "AST_term_node.h"

class AST_arithmetic_term_node : public virtual AST_term_node {

    public:
        AST_arithmetic_term_node(unsigned level, string value);

        virtual void accept(visitor * v);
};

#include "../visitor/visitor.h"

#endif //LEXER_AST_ARITHMETIC_TERM_NODE_H
