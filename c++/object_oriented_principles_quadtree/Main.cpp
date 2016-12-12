#include <fstream>
#include <string>
#include <iostream>

#ifndef BOOLEAN
    #define BOOLEAN
    #include "Boolean.h"
#endif

#ifndef COLOR
    #define COLOR
    #include "Color.h"
#endif

#ifndef FILE
    #define FILE
    #include "File.h"
#endif

#ifndef FILE_CPP
    #define FILE_CPP
    #include "File.cpp"
#endif

#ifndef INVALIDINPUT
    #define INVALIDINPUT
    #include "InvalidInputException.h"
#endif

#ifndef MONOCHROME
    #define MONOCHROME
    #include "Monochrome.h"
#endif

#ifndef NODE
    #define NODE
    #include "Node.h"
#endif

#ifndef NODE_CPP
    #define NODE_CPP
    #include "Node.cpp"
#endif

#ifndef QUADTREE
    #define QUADTREE
    #include "QuadTree.h"
#endif

#ifndef QUADTREE_CPP
    #define QUADTREE_CPP
    #include "QuadTree.cpp"
#endif

using namespace std;
using namespace color;

void printCommands() {
    cout << "Commands: " << endl;
    cout << "\tload type filename - load the given quadtree file having the indicated color type" << endl;
    cout << "\tsave filename - save the current quadtree file" << endl;
    cout << "\tconvert type filename - convert the given image file made up of the indicated color type" << endl;
    cout << "\tshow - print the current quadtree" << endl;
    cout << "\thelp - show this text" << endl;
    cout << "\tquit - quit the program" << endl;
}

void printTypes() {
    cout << "Colors: " << endl;
    cout << "\tBoolean" << endl;
    cout << "\tColor" << endl;
    cout << "\tMonochrome" << endl;
}

void printHelp() {
    cout << "Please enter the commands in the following format. The type and filename may be omitted as indicated: " << endl;
    cout << "command [type] [filename]" << endl;
    printCommands();
    printTypes();
}

string toLower(string s) {
    string lower = "";
    for (unsigned i = 0; i < s.length(); i++) {
        lower += tolower(s[i]);
    }
    return lower;
}

string getCommand(string line) {
    unsigned position;
    if ((position = line.find(" ")) != string::npos) {
        return line.substr(0, position);
    } else {
        return line;
    }
}

string getType(string line) {
    unsigned start, end;
    start = line.find(" ");
    end = line.find_last_of(" ");
    if ((start == string::npos) && (end == string::npos)) { // if there are no spaces, then there is no type
        return string("");
    } else if (start == end) { // if start and end are the same, then there is only one parameter, which would be the filename
        return string("");
    } else {
        return line.substr(start + 1, end - start - 1);
    }
}

string getFileName(string line) {
    unsigned start;
    start = line.find_last_of(" ");
    if (start == string::npos) { // if there are no spaces, then there is no type
        return string("");
    } else {
        return line.substr(start + 1);
    }
}

int main (int argc, char ** argv) {
    printHelp();
    string input;
    bool quadtree_exists = false;
    string quadtree_type = "";
    string command = "", type = "", filename = "";
    QuadTree<Boolean> * boolean_quadtree = new QuadTree<Boolean>(0, 0);
    QuadTree<Monochrome> * monochrome_quadtree = new QuadTree<Monochrome>(0, 0);
    QuadTree<Color> * color_quadtree = new QuadTree<Color>(0, 0);
    do {
        cout << "Enter a command: ";
        getline(cin, input);
        input = toLower(input);
        command = getCommand(input);
        type = getType(input);
        filename = getFileName(input);
        
        try {
            if (command.compare("help") == 0) {
                printHelp();
            } else if (command.compare("load") == 0) {
                if (type.compare("boolean") == 0) {
                    boolean_quadtree = File<Boolean>::load(filename);
                    quadtree_type = "boolean";
                    quadtree_exists = true;
                    cout << filename << " loaded" << endl;
                } else if (type.compare("color") == 0) {
                    color_quadtree = File<Color>::load(filename);
                    quadtree_type = "color";
                    quadtree_exists = true;
                    cout << filename << " loaded" << endl;
                } else if (type.compare("monochrome") == 0) {
                    monochrome_quadtree = File<Monochrome>::load(filename);
                    quadtree_type = "monochrome";
                    quadtree_exists = true;
                    cout << filename << " loaded" << endl;
                } else {
                    cout << "Unknown type!" << endl;
                    printTypes();
                }
            } else if (command.compare("save") == 0) {
                if (quadtree_type.compare("boolean") == 0) {
                    File<Boolean>::save(*boolean_quadtree, filename);
                    cout << "Saved quadtree to " << filename << endl;
                } else if (quadtree_type.compare("color") == 0) {
                    File<Color>::save(*color_quadtree, filename);
                    cout << "Saved quadtree to " << filename << endl;
                } else if (quadtree_type.compare("monochrome") == 0) {
                    File<Monochrome>::save(*monochrome_quadtree, filename);
                    cout << "Saved quadtree to " << filename << endl;
                } else {
                    cout << "Unknown type!" << endl;
                    printTypes();
                }
            } else if (command.compare("convert") == 0) {
                if (type.compare("boolean") == 0) {
                    File<Boolean> * file = new File<Boolean>(filename);
                    boolean_quadtree = file->getQuadTree();
                    delete file;
                    quadtree_type = "boolean";
                    quadtree_exists = true;
                    cout << "Loaded image from " << filename << endl;
                } else if (type.compare("color") == 0) {
                    File<Color> * file = new File<Color>(filename);
                    color_quadtree = file->getQuadTree();
                    delete file;
                    quadtree_type = "color";
                    quadtree_exists = true;
                    cout << "Loaded image from " << filename << endl;
                } else if (type.compare("monochrome") == 0) {
                    File<Monochrome> * file = new File<Monochrome>(filename);
                    monochrome_quadtree = file->getQuadTree();
                    delete file;
                    quadtree_type = "monochrome";
                    quadtree_exists = true;
                    cout << "Loaded image from " << filename << endl;
                } else {
                    cout << "Unknown type!" << endl;
                    printTypes();
                }
            } else if (command.compare("show") == 0) {
                if (quadtree_exists) {
                    if (quadtree_type.compare("boolean") == 0) {
                        boolean_quadtree->print();
                    } else if (quadtree_type.compare("color") == 0) {
                        color_quadtree->print();
                    } else if (quadtree_type.compare("monochrome") == 0) {
                        monochrome_quadtree->print();
                    }
                } else {
                    cout << "No quadtree has been loaded yet" << endl;
                }
            } else if (command.compare("quit") != 0) {
                cout << "Unknown command!" << endl;
                printHelp();
            }
        } catch(FileNotFoundException e) {
            cout << e.getMessage() << endl;
        } catch (IncorrectFileExtensionException e) {
            cout << e.getMessage() << endl;
        } catch (IncorrectInputException e) {
            cout << e.getMessage() << endl;
        }
    } while (command.compare("quit") != 0);
    delete boolean_quadtree;
    delete color_quadtree;
    delete monochrome_quadtree;
    return 0;
}
