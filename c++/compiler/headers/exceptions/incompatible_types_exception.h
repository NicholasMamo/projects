//
// Created by memonick on 19/04/2016.
//

#ifndef LEXER_INCOMPATIBLE_TYPES_EXCEPTION_H
#define LEXER_INCOMPATIBLE_TYPES_EXCEPTION_H

#include "../symbol_table/symbol.h"
#include "general_exception.h"

#include <string>

using namespace std;

class incompatible_types_exception: public general_exception {

    public:
        incompatible_types_exception(var_type type_1);
        incompatible_types_exception(var_type type_1, var_type type_2);

        virtual string to_string();

    public:
        bool has_type_1 = false;
        bool has_type_2 = false;
        var_type type_1;
        var_type type_2;

};

#endif //LEXER_INCOMPATIBLE_TYPES_EXCEPTION_H
