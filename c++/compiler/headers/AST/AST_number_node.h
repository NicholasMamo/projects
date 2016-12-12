//
// Created by memonick on 15/03/2016.
//

using namespace std;

#ifndef LEXER_AST_NUMBER_NODE_H
#define LEXER_AST_NUMBER_NODE_H

#include "AST_node.h"
#include <string>

class AST_number_node : public virtual AST_node {

    public:
        AST_number_node(unsigned level, string value);
        virtual ~AST_number_node();

        void set_value(string value);

        string get_value();

        virtual void accept(visitor * v) = 0;

    private:
        string value;

};

#endif //LEXER_AST_NUMBER_NODE_H
