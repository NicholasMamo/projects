//
// Created by memonick on 20/04/2016.
//

#ifndef LEXER_EXCEPTION_H
#define LEXER_EXCEPTION_H

#include <string>

using namespace std;

class general_exception {

    public:
        virtual string to_string() = 0;

};

#endif //LEXER_EXCEPTION_H
