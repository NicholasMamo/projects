#include <fstream>
#include <string>
#include <vector>

#ifndef FILE
    #define FILE
    #include "File.h"
#endif

#ifndef IMAGEELEMENT
    #define IMAGEELEMENT
    #include "ImageElement.h"
#endif

#ifndef INVALIDINPUT
    #define INVALIDINPUT
    #include "InvalidInputException.h"
#endif

#ifndef NODE
    #define NODE
    #include "Node.h"
#endif

#ifndef QUADTREE
    #define QUADTREE
    #include "QuadTree.h"
#endif

using namespace std;

namespace color {
    class Boolean: public ImageElement {
            
        public:
            Boolean();
            Boolean(string value);
            
            void setValue(string value);
            bool getBoolean() const;
            string getValue() const;
            
            bool operator== (const Boolean &boolean) const;
            
            void validate(string s);
            void print();
            
            static QuadTree<Boolean> * parse(unsigned lines, unsigned characters,  ifstream &file);
            static Boolean parseLine(string line);

    };
}
