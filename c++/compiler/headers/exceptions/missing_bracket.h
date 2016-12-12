//
// Created by memonick on 09/04/2016.
//

#ifndef LEXER_MISSING_BRACKET_H
#define LEXER_MISSING_BRACKET_H

#include "parse_exception.h"

#include <string>

using namespace std;

class missing_bracket : public parse_exception {

    public:
        missing_bracket(char bracket, unsigned line);

        virtual string to_string();

    private:
        char bracket;
};

#endif //LEXER_MISSING_BRACKET_H
