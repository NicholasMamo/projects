//
// Created by memonick on 17/04/2016.
//

#ifndef LEXER_REPL_H
#define LEXER_REPL_H

class lexer;
class parser;

#include "file.h"
#include "lexer.h"
#include "parser.h"
#include "AST/AST_program_node.h"
#include "visitor/interpreter_visitor.h"
#include "visitor/printer_visitor.h"
#include "visitor/semantic_visitor.h"

#include <iostream>
#include <string>

using namespace std;

enum repl_keyword {REPL_quit, REPL_load, REPL_st, REPL_print, REPL_other};

class repl {

    public:
        repl();
        ~repl();
        void run();

        string keyword_to_string(repl_keyword command);

    private:
        lexer * l = nullptr;
        parser * p = nullptr;
        semantic_visitor *  s = nullptr;
        interpreter_visitor * i = nullptr;

        void execute_command(string command_string, repl_keyword command_keyword);
        string get_command();
        string get_key(string command);
        repl_keyword interpret_command(string command);

        void print_tokens(lexer * l);
        string get_tree(AST_program_node * program_node);
        bool analyze_semantics(AST_program_node * program_node);
        void interpret(AST_program_node * program_node);
};

#include "lexer.h"
#include "parser.h"

#endif //LEXER_REPY_H