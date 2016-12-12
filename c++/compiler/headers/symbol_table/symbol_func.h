//
// Created by memonick on 19/04/2016.
//

#ifndef LEXER_SYMBOL_FUNC_H
#define LEXER_SYMBOL_FUNC_H

#include "../AST/AST_block_node.h"
#include "../AST/AST_formal_parameters_node.h"
#include "symbol.h"

#include <string>

using namespace std;

class symbol_func : public symbol {

    public:
        symbol_func(string);

        void set_body(AST_block_node * body);
        void set_parameters(AST_formal_parameters_node * parameters);

        AST_block_node * get_body();
        AST_formal_parameters_node * get_parameters();

        virtual string to_string();

    private:
        AST_block_node * body = nullptr;
        AST_formal_parameters_node * parameters = nullptr;

};

#endif //LEXER_SYMBOL_FUNC_H
