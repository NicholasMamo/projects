//
// Created by memonick on 20/04/2016.
//

#ifndef LEXER_INCORRECT_RETURN_TYPE_EXCEPTION_H
#define LEXER_INCORRECT_RETURN_TYPE_EXCEPTION_H

#include "../symbol_table/symbol.h"
#include "general_exception.h"

#include <string>

using namespace std;

class incorrect_return_type_exception : public general_exception {

    public:
        incorrect_return_type_exception(var_type found, var_type required);

        virtual string to_string();

    private:
        var_type found;
        var_type required;

};

#endif //LEXER_INCORRECT_RETURN_TYPE_EXCEPTION_H
