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
    class Monochrome: public ImageElement {
            
        public:
            Monochrome();
            Monochrome(string value);
            
            void setValue(string value);
            string getValue() const;
            
            bool operator== (const Monochrome &Monochrome) const;
            
            void validate(string s);
            void print();
            
            static QuadTree<Monochrome> * parse(unsigned lines, unsigned characters,  ifstream &file);
            static Monochrome parseLine(string line);

    };
}
