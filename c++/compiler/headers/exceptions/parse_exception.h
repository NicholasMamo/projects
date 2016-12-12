//
// Created by memonick on 11/04/2016.
//

#ifndef LEXER_EXCEPTION_H_H
#define LEXER_EXCEPTION_H_H

#include "general_exception.h"

class parse_exception : public general_exception {

    public:
        parse_exception(unsigned line);

        void set_line(unsigned line);

        unsigned get_line();

        virtual string to_string() = 0;

    protected:
        unsigned line;
};

#endif //LEXER_EXCEPTION_H_H
