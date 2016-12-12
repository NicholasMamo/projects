//
// Created by memonick on 20/04/2016.
//

#ifndef LEXER_UNDECLARED_VAR_EXCEPTION_H
#define LEXER_UNDECLARED_VAR_EXCEPTION_H

#include "general_exception.h"

#include <string>

using namespace std;

class undeclared_var_exception: public general_exception {

    public:
        undeclared_var_exception(string name);
        
        virtual string to_string();
        
    private:
        string name;

};

#endif //LEXER_UNDECLARED_VAR_EXCEPTION_H
