//
// Created by memonick on 29/02/2016.
//

#include <iostream>
#include <fstream>
#include <string>

#ifndef LEXER_FILE_H
    #include "../headers/file.h"
    #define LEXER_FILE_H
#endif

using namespace std;

/**
 * Convert the file at the given path into a string
 * path             the path to the file that will be converted into a string
 * return           the file, converted into a string
 */
string file::getFileString(string path) {
    string file_contents = "";
    ifstream file;

    file.open(path, ios::in); // open the file
    if (file.is_open()) { // if the file was opened correctly
        string line;
        while (getline(file, line)) { // read line by line
            file_contents += line; // append the line
            file_contents += '\n'; // append the newline character, that would not have been read
        }
    }
    return file_contents;
}

/**
 * Save a file to the given path and with the given filename, and store in it the contents given
 * path             the path where the file will be saved
 * filename         the name of the file
 * contents         the contents of the file
 */
void file::save(string path, string filename, string contents) {
    ofstream outFile;
    outFile.open(path + filename);
    outFile << contents;
    outFile.close(); // close file
}