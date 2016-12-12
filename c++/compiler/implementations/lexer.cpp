//
// Created by memonick on 01/03/2016.
//

#include <iostream>

#include "../headers/lexer.h"
#include "../headers/token.h"

using namespace std;

/**
 * Create a lexer with the given program
 * program          the program on which lexical analysis will be performed
 */
lexer::lexer(string program) {
    this->program = program;
}

/**
 * Create a lexer without any program
 */
lexer::lexer() {}

/**
 * Set the program of the lexer to the given one
 * string           the new program of the lexer
 */
void lexer::set_program(string program) {
    this->program = program;
}

/**
 * Get the program of the lexer
 * return           the program of the lexer
 */
string lexer::get_program() {
    return this->program;
}

/**
 * Get the next token from the program being analyzed
 * return           the next token in the file
 */
token * lexer::get_next_token() {
    token * tok = new token();

    if (!is_string) {
        this->skip();
        this->skip_comments();
    }

    // determine what type of token is being read
    this->fetch_name(tok);

    // read token attribute
    this->fetch_attribute(tok);

    // give the token the line number where it appears
    tok->set_line(this->line);

    // postprocess the token
    this->postprocess(tok);

    return tok;
}

/**
 * Peek at the next token from the program being analyzed
 * return           the next token in the file
 */
token * lexer::peek() {
    return this->peek(0);
}

/**
 * Peek at the nth token from the program being analyzed, with the next token being token 0
 * n                the number of tokens from the next one to get
 * return           the next token in the file
 */
token * lexer::peek(int n) {
    if (n == 0) {
        bool temp_is_string = this->is_string;
        unsigned line = this->line; // store the current line number to revert to it
        int position = this->position; // store the current position to revert to it
        token * tok = this->get_next_token(); // get the next token
        this->position = position; // revert to the original position
        this->line = line; // revert to the original line
        this->is_string = temp_is_string;
        return tok;
    } else if (n > 0) {
        bool temp_is_string = this->is_string;
        unsigned line = this->line; // store the current line number to revert to it
        int position = this->position; // store the current position to revert to it
        this->get_next_token(); // get the next token
        token * ret = this->peek(n - 1); // recursively peek at the next tokens
        this->position = position; // revert to the original position
        this->line = line; // revert to the original line
        this->is_string = temp_is_string;
        return ret;
    } else {
        return new token();
    }
}

/**
 * Check whether the lexer is at the end of the file
 * return           a boolean indicating whether the lexer is at the end of the file (true), or not (false)
 */
bool lexer::at_eof() {
    token * next = this->peek();
    return (next->get_name() == TOK_eof);
}

/**
 * Reset the position marker of the lexer
 */
void lexer::reset() {
    this->position = 0;
    this->line = 0;
    this->is_string = false;
}

/**
 * Fetch the name of the next token
 */
void lexer::fetch_name(token * t) {
    if (this->position >= this->program.length() - 1) { // if at eof, return eof token
        t->set_name(TOK_eof);
    } else {
        char c = this->program.at(this->position);
        if (is_string && !is_string_start(c)) {
            t->set_name(TOK_string);
        } else if (is_bracket(c)) {
            t->set_name(TOK_bracket);
        } else if (is_comma(c)) {
            t->set_name(TOK_comma);
        } else if (is_eos(c)) {
            t->set_name(TOK_eos);
        } else if (is_number(c)) {
            t->set_name(TOK_int_number);
        } else if (is_boolean_operator()) {
            t->set_name(TOK_boolean);
        } else if (is_simple_assignment()) {
            t->set_name(TOK_simple_assignment);
        } else if (is_string_start(c)) {
            is_string = !is_string;
            t->set_name(TOK_string_start);
        } else if (is_colon(c)) {
            t->set_name(TOK_colon);
        } else if (is_assignment()) {
            t->set_name(TOK_assignment);
        } else if (is_operator(c)) {
            t->set_name(TOK_arithmetic);
        } else if (is_identifier(c)) {
            t->set_name(TOK_identifier);
        } else {
            t->set_name(TOK_unknown);
        }
    }
}

/**
 * Fetch the attribute of the next token
 */
void lexer::fetch_attribute(token * t) {
    string attribute = "";
    switch (t->get_name()) {
        case TOK_string:
            attribute = this->get_string();
            break;
        case TOK_bracket:
            attribute = this->get_bracket();
            break;
        case TOK_comma:
            attribute = this->get_comma();
            break;
        case TOK_eos:
            attribute = this->get_eos();
            break;
        case TOK_int_number:
            attribute = this->get_number();
            break;
        case TOK_boolean:
            attribute = this->get_boolean_operator();
            break;
        case TOK_simple_assignment:
            attribute = this->get_simple_assignment();
            break;
        case TOK_string_start:
            attribute = this->get_string_start();
            break;
        case TOK_colon:
            attribute = this->get_colon();
            break;
        case TOK_assignment:
            attribute = this->get_assignment();
            break;
        case TOK_arithmetic:
            attribute = this->get_operator();
            break;
        case TOK_identifier:
            attribute = this->get_identifier();
            break;
    }
    t->set_attribute(attribute);
}

/**
 * Postprocess the given token
 */
void lexer::postprocess(token * t) {
    if (t->get_name() == TOK_identifier) {
        this->check_keyword(t);
    } else if (t->get_name() == TOK_int_number) {
        this->check_real(t);
    }
}

/**
 * Skip whitespaces, newlines and tabs before the next token
 */
void lexer::skip() {
    char c = this->program.at(this->position);
    while ((c == ' ' || c == '\n' || c == '\t') && this->position < this->program.length() - 1) { // skip whitespaces. newlines and tabs
        if (c == '\n') {
            this->line++;
        }
        this->position++;
        c = this->program.at(this->position);
    }
}

/**
 * Skip comments before the next token
 */
void lexer::skip_comments() {
    bool comments;
    do {
        comments = false;
        if (this->position < this->program.length() - 2) { // if there are at least two more characters remaining
            if (this->program.at(this->position) == '/' && this->program.at(this->position + 1) == '/') { // if the two next characters indicate a single-line comment
                comments = true;
                this->position += 2; // move two characters forward
                while (this->program.at(this->position) != '\n' && this->position < this->program.length() - 1) {
                    this->position++;
                }
            } else if (this->program.at(this->position) == '/' && this->program.at(this->position + 1) == '*') { // if the two next characters indicate a block comment
                comments = true;
                this->position += 2; // move two characters forward
                while (this->position < this->program.length() - 2 && !(this->program.at(this->position) == '*' && this->program.at(this->position + 1) == '/')) {
                    if (this->program.at(this->position) == '\n') {
                        this->line++;
                    }
                    this->position++;
                }
                if (this->position < this->program.length() - 2) {
                    this->position += 2;
                }
            }
        }
        this->skip(); // skip any whitespaces or newlines you find
    } while (comments);
}

/**
 * Check whether the provided character is a bracket or not
 * c                the character to check
 * return           a boolean indicating whether the character is a bracket (true), or not (false)
 */
bool lexer::is_bracket(char c) {
    return (c == '(' || c == ')' || c == '{' || c == '}');
}

/**
 * Check whether the provided character is a comma or not
 * c                the character to check
 * return           a boolean indicating whether the character is a comma (true), or not (false)
 */
bool lexer::is_comma(char c) {
    return (c == ',');
}

/**
 * Check whether the provided character indicates the end of a statement or not
 * c                the character to check
 * return           a boolean indicating whether the character indicates the end of a statement (true), or not (false)
 */
bool lexer::is_eos(char c) {
    return c == ';';
}

/**
 * Check whether the provided character is a number or not
 * c                the character to check
 * return           a boolean indicating whether the character is a number (true), or not (false)
 */
bool lexer::is_number(char c) {
    return (c >= 48 && c <= 57);
}

/**
 * Check whether the next token is an boolean operator or not
 * return           a boolean indicating whether the next token is a boolean operator (true), or not (false)
 */
bool lexer::is_boolean_operator() {
    if (this->position < this->program.length() - 1) {
        char next = this->program.at(this->position);
        if (next == '<' || next == '>' || next == '!') { // if the next character is an angle bracket
            return true; // then it must be a boolean operator
        } else if (next == '=' && this->position < this->program.length() - 2) { // if the next character is an equality sign
            if (this->program.at(this->position + 1) == '=') { // and the one after that is also an equality sign
                return true; // then it is a boolean operator as well
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

/**
 * Check whether the provided character is an arithmetic operator or not
 * c                the character to check
 * return           a boolean indicating whether the character is an arithmetic operator (true), or not (false)
 */
bool lexer::is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

/**
 * Check whether the provided character is an assignment (an operator followed by an equality sign) or not
 * c                the character to check
 * return           a boolean indicating whether the character is an assignment (an operator followed by an equality sign) (true), or not (false)
 */
bool lexer::is_assignment() {
    if (this->position < this->program.length() - 2) {
        if (is_operator(this->program.at(this->position)) && this->program.at(this->position + 1) == '=') { // check if the next sequence is an arithmetic operator followed by an equality sign
            return true;
        }
    }
    return (this->program.at(this->position) == '=');
}

/**
 * Check whether the provided character is a simple assignment (++ or --) or not
 * c                the character to check
 * return           a boolean indicating whether the character is a simple assignment (++ or --) (true), or not (false)
 */
bool lexer::is_simple_assignment() {
    if (this->position < this->program.length() - 2) {
        if (this->program.at(this->position) == '+' && this->program.at(this->position + 1) == '+') { // check if the next sequence is ++
            return true;
        } else if (this->program.at(this->position) == '-' && this->program.at(this->position + 1) == '-') { // check if the next sequence is --
            return true;
        }
    }
    return false;
}

/**
 * Check whether the provided character is the start of a string or not
 * c                the character to check
 * return           a boolean indicating whether the character is the start of a string (true), or not (false)
 */
bool lexer::is_string_start(char c) {
    return c == '"';
}

/**
 * Check whether the provided character is a colon or not
 * c                the character to check
 * return           a boolean indicating whether the character is a colon (true), or not (false)
 */
bool lexer::is_colon(char c) {
    return c == ':';
}

/**
 * Check whether the provided character is the start of an identifier or not
 * c                the character to check
 * return           a boolean indicating whether the character is the start of an identifier (true), or not (false)
 */
bool lexer::is_identifier(char c) {
    return ((c >= 97 && c <= 122) || (c >= 65 && c <= 90) || c == 95);
}

/**
 * Get the next bracket from the program
 * return           the next bracket from the program
 */
string lexer::get_bracket() {
    string bracket = "";
    bracket += this->program.at(this->position++);
    return bracket;
}

/**
 * Get the next comma from the program
 * return           the next comma from the program
 */
string lexer::get_comma() {
    string comma = "";
    comma += this->program.at(this->position++);
    return comma;
}

/**
 * Get the next end of statement symbol from the program
 * return           the next end of statement symbol from the program
 */
string lexer::get_eos() {
    string eos = "";
    eos += this->program.at(this->position++);
    return eos;
}

/**
 * Get the next number from the program
 * return           the next number from the program
 */
string lexer::get_number() {
    string number = "";
    bool period = false;
    while ((is_number(this->program.at(this->position)) || (this->program.at(this->position) == '.' && !period)) &&
           this->position < this->program.length() - 1) { // if it is a number
        if (this->program.at(this->position) == '.') {
            period = true;
        }
        number += this->program.at(this->position);
        this->position++;
    }
    return number;
}

/**
 * Get the next boolean operator from the program
 * return           the next boolean operator from the program
 */
string lexer::get_boolean_operator() {
    string op = "";
    if (this->position < this->program.length() - 1) {
        char next = this->program.at(this->position);
        if (next == '<' || next == '>' || next == '!') { // if the next character is an angle bracket
            op += next;
            this->position++;
            next = this->program.at(this->position);
            if (this->position < this->program.length() - 1) {
                if (next == '=') { // if the next character is an angle bracket
                    this->position++;
                    op += next;
                } else {
                    return op;
                }
            }
        } else if (next == '=' && this->position < this->program.length() - 2) { // if the next character is an equality sign
            this->position += 2;
            return "==";
        }
    }

    return op;
}

/**
 * Get the next operator from the program
 * return           the next operator from the program
 */
string lexer::get_operator() {
    string op = "";
    if (is_operator(this->program.at(this->position))) { // if it is an arithmetic symbol
        op = this->program.at(this->position);
        this->position++;
    }
    return op;
}

/**
 * Get the next assignment from the program
 * return           the next assignment from the program
 */
string lexer::get_assignment() {
    string assignment = "";
    assignment += this->program.at(this->position++);
    if (this->program.at(this->position) == '=') {
        assignment += this->program.at(this->position++);
    }
    return assignment;
}

/**
 * Get the next simple assignment from the program
 * return           the next simple assignment from the program
 */
string lexer::get_simple_assignment() {
    string assignment = "";
    assignment += this->program.at(this->position++);
    assignment += this->program.at(this->position++);
    return assignment;
}

/**
 * Get the next string start from the program
 * return           the next string start from the program
 */
string lexer::get_string_start() {
    string string_start = "";
    string_start += this->program.at(this->position++);
    return string_start;
}

/**
 * Get the string from the program
 * return           the next string start from the program
 */
string lexer::get_string() {
    string identifier = "";
    char c = this->program.at(this->position);
    while (!is_string_start(c) && this->position < this->program.length() - 1) { // if it is not an inverted comma
        identifier += c;
        this->position++;
        c = this->program.at(this->position);
    }
    return identifier;
}

/**
 * Get the next colon from the program
 * return           the next colon from the program
 */
string lexer::get_colon() {
    string colon = "";
    colon += this->program.at(this->position++);
    return colon;
}

/**
 * Get the next identifier from the program
 * return           the next identifier from the program
 */
string lexer::get_identifier() {
    string identifier = "";
    char c = this->program.at(this->position);
    while ((is_identifier(c) || is_number(c) || c == 95) &&
           this->position < this->program.length() - 1) { // if it is an identifier
        identifier += c;
        this->position++;
        c = this->program.at(this->position);
    }
    return identifier;
}

/**
 * Check whether the given token is a keyword or not
 */
void lexer::check_keyword(token * t) {
    string attribute = t->get_attribute();
    for (unsigned i = 0; i < sizeof(this->KEYWORDS)/sizeof(string); i++) {
        if (attribute == this->KEYWORDS[i]) {
            t->set_name(TOK_keyword);
        }
    }

    for (unsigned i = 0; i < sizeof(this->BOOL_LITERAL)/sizeof(string); i++) {
        if (attribute == this->BOOL_LITERAL[i]) {
            t->set_name(TOK_bool_literal);
        }
    }

    for (unsigned i = 0; i < sizeof(this->BOOL_OPERATOR)/sizeof(string); i++) {
        if (attribute == this->BOOL_OPERATOR[i]) {
            t->set_name(TOK_boolean_operator);
        }
    }

    for (unsigned i = 0; i < sizeof(this->TYPES)/sizeof(string); i++) {
        if (attribute == this->TYPES[i]) {
            t->set_name(TOK_var_type);
        }
    }
}

/**
 * Check whether the given token is a real number or not
 */
void lexer::check_real(token * t) {
    string attribute = t->get_attribute();
    for (unsigned i = 0; i < attribute.size(); i++) {
        if (attribute.at(i) == '.') {
            t->set_name(TOK_real_number);
        }
    }
}