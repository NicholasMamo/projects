//
// Created by memonick on 13/04/2016.
//

#ifndef LEXER_AST_BOOLEAN_LITERAL_NODE_H
#define LEXER_AST_BOOLEAN_LITERAL_NODE_H

#include "AST_node.h"
#include "../visitor/visitor.h"
#include <string>

class AST_boolean_node : public virtual AST_node {

    public:
        AST_boolean_node(unsigned level, string value);
        virtual ~AST_boolean_node();

        void set_bool_value(bool bool_value);

        bool get_bool_value();

        virtual void accept(visitor * v);

    private:
        bool bool_value;

};

#endif //LEXER_AST_BOOLEAN_LITERAL_NODE_H
