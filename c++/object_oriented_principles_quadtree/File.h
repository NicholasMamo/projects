#include <fstream>
#include <string>
#include <vector>

#include "FileNotFoundException.h"
#include "IncorrectFileExtensionException.h"

#ifndef INCORRECTINPUTEXCEPTION
    #define INCORRECTINPUTEXCEPTION
    #include "IncorrectInputException.h"
#endif

#ifndef COORDINATEUNBOUND
    #define COORDINATEUNBOUND
    #include "CoordinateUnboundException.h"
#endif

#ifndef QUADTREE
    #define QUADTREE
    #include "QuadTree.h"
#endif

template <typename Object>
class File {

    private:
        ifstream file;
        
        unsigned getLineLength();
        unsigned getLines();
        
    public:
        static const string DELIMETER;
    
        File(string filename);
        ~File();
        
        QuadTree<Object> * getQuadTree();
        static void save(QuadTree<Object> &quadtree, string filename);
        static QuadTree<Object> * load(string name);
        
        void print();

};
