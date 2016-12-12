//
// Created by memonick on 20/04/2016.
//

#ifndef LEXER_INCORRECT_PARAMETER_COUNT_H
#define LEXER_INCORRECT_PARAMETER_COUNT_H

#include "general_exception.h"

#include <string>

using namespace std;

class incorrect_parameter_count: public general_exception {

    public:
        incorrect_parameter_count(unsigned long found, unsigned long required);

        virtual string to_string();

    private:
        unsigned long found = 0;
        unsigned long required = 0;

};

#endif //LEXER_INCORRECT_PARAMETER_COUNT_H
