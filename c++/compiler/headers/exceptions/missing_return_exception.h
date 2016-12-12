//
// Created by memonick on 20/04/2016.
//

#ifndef LEXER_MISSING_RETURN_EXCEPTION_H
#define LEXER_MISSING_RETURN_EXCEPTION_H

#include "../symbol_table/symbol.h"
#include "general_exception.h"

#include <string>

using namespace std;

class missing_return_exception : public general_exception {

    public:
        missing_return_exception(var_type type);

        virtual string to_string();

    private:
        var_type type;

};

#endif //LEXER_MISSING_RETURN_EXCEPTION_H
