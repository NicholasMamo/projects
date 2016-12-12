//
// Created by memonick on 09/04/2016.
//

#include "../../headers/exceptions/missing_bracket.h"

missing_bracket::missing_bracket(char bracket, unsigned line) : parse_exception(line) {
    this->bracket = bracket;
}

string missing_bracket::to_string() {
    string s = "";
    s += "Missing bracket, expected '";
    s += this->bracket + "'";
    s += " on line ";
    s += std::to_string(this->line) + "\n";
    return s;
}