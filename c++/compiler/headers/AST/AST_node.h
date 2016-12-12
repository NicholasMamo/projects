//
// Created by memonick on 15/03/2016.
//

#include <sstream>
#include <string>

using namespace std;

#ifndef LEXER_AST_NODE_H
#define LEXER_AST_NODE_H

class visitor;

class AST_node {

    public:
        virtual ~AST_node() {};
        virtual void set_level(unsigned level);

        unsigned get_level();

        virtual void accept(visitor * v) = 0;

    protected:
        unsigned level;

};

#endif //LEXER_AST_NODE_H
