//
// Created by memonick on 13/04/2016.
//

#ifndef LEXER_AST_INT_NUMBER_NODE_H
#define LEXER_AST_INT_NUMBER_NODE_H

#include "AST_number_node.h"
#include "../visitor/visitor.h"

class AST_int_number_node : public virtual AST_number_node {

    public:
        AST_int_number_node(int level, string value);

        void set_int_value(int int_value);

        int get_int_value();

        virtual void accept(visitor * v);

    private:
        int int_value;
};

#endif //LEXER_AST_INT_NUMBER_NODE_H
