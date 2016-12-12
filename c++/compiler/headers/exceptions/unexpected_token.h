//
// Created by memonick on 09/04/2016.
//

#ifndef LEXER_UNEXPECTEDTOKEN_H
#define LEXER_UNEXPECTEDTOKEN_H

#include "parse_exception.h"
#include "../token.h"

#include <string>

using namespace std;

class unexpected_token : public parse_exception {

    public:
        unexpected_token(name found, unsigned line);
        unexpected_token(name found, name required, unsigned line);

        virtual string to_string();

    private:
        name found;
        name required;

};

#endif //LEXER_UNEXPECTEDTOKEN_H
