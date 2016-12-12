//
// Created by memonick on 29/02/2016.
//

#include <string>

using namespace std;

#ifndef LEXER_FILE_H
#define LEXER_FILE_H

class file {

    public:
        static string getFileString(string path);

        static void save(string path, string filename, string contents);

};

#endif //LEXER_FILE_H