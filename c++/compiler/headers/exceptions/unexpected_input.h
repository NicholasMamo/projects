//
// Created by memonick on 11/04/2016.
//

#ifndef LEXER_UNEXPECTED_INPUT_H
#define LEXER_UNEXPECTED_INPUT_H

#include "parse_exception.h"

#include <string>

using namespace std;

class unexpected_input : public parse_exception {

    public:
        unexpected_input(string found, unsigned line);
        unexpected_input(string found, string required, unsigned line);

        virtual string to_string();

    private:
        string found;
        string required;

};

#endif //LEXER_UNEXPECTED_INPUT_H
