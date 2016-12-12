#include <iostream>
#include <string>

#include "headers/repl.h"

using namespace std;

int main() {
    ///home/memonick/Documents/School/Semester 4/CPS2000 - Compiler Theory and Practice/Assignment/Lexer/resources/program.mini
    repl * mini_lang_i = new repl();
    mini_lang_i->run();
    delete mini_lang_i;
    return 0;
}