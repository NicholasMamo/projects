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
    class Color: public ImageElement {

        private:
            string red, green, blue;
            
        public:
            Color();
            Color(string red, string green, string blue);
            
            void setRed(string red);
            void setGreen(string green);
            void setBlue(string blue);
            void setValue(string value);
            string getRed();
            string getGreen();
            string getBlue();
            string getValue() const;
            void updateValue();
            
            bool operator== (const Color &color) const;
            
            void validate(string s);
            void print();
            
            static QuadTree<Color> * parse(unsigned lines, unsigned characters,  ifstream &file);
            static Color parseLine(string line);

    };
}
