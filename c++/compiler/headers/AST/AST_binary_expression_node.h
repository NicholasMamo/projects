//
// Created by memonick on 15/03/2016.
//

#ifndef LEXER_AST_BOOLEAN_EXPRESSION_H
#define LEXER_AST_BOOLEAN_EXPRESSION_H

#include "AST_node.h"
#include <string>

class visitor;

class AST_binary_expression_node: public virtual AST_node {

    public:
        AST_binary_expression_node(unsigned level, string value);
        virtual ~AST_binary_expression_node();

        void set_value(string value);
        void set_left_child(AST_node * left_child);
        void set_right_child(AST_node * right_child);

        string get_value();
        bool contains_left_child();
        bool contains_right_child();
        AST_node * get_left_child();
        AST_node * get_right_child();

        virtual void accept(visitor * v) = 0;
        virtual void set_level(unsigned level);

    protected:
        string value;
        AST_node * left_child;
        AST_node * right_child;
        bool has_left_child = false;
        bool has_right_child = false;

};

#endif //LEXER_AST_BOOLEAN_EXPRESSION_H
