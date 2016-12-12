//
// Created by memonick on 19/04/2016.
//

#ifndef LEXER_STACK_EMPTY_EXCEPTION_H
#define LEXER_STACK_EMPTY_EXCEPTION_H

#include "general_exception.h"

#include <string>

using namespace std;

class stack_empty_exception : public general_exception {

    public:
        stack_empty_exception();

        virtual string to_string();

    private:
        string message = "stack empty exception";

};

#endif //LEXER_STACK_EMPTY_EXCEPTION_H
