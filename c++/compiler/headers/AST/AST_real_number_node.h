//
// Created by memonick on 13/04/2016.
//

#ifndef LEXER_AST_REAL_NUMBER_NODE_H
#define LEXER_AST_REAL_NUMBER_NODE_H

#include "AST_number_node.h"
#include "../visitor/visitor.h"

class AST_real_number_node : public virtual AST_number_node {

    public:
        AST_real_number_node(int level, string value);

        void set_real_value(double real_value);

        double get_real_value();

        virtual void accept(visitor * v);

    private:
        double real_value;

};

#endif //LEXER_AST_REAL_NUMBER_NODE_H
