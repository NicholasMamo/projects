#include <vector>

#ifndef COORDINATEUNBOUND
    #define COORDINATEUNBOUND
    #include "CoordinateUnboundException.h"
#endif

#include "CoordinateOutOfBoundsException.h"

#ifndef NODE
    #define NODE
    #include "Node.h"
#endif

template <class Object>
class QuadTree {

    private:
        unsigned width; // the width of the QuadTree
        unsigned height; // the height of the QuadTree
        unsigned x; // the starting x-coordinate of the QuadTree
        unsigned y; // the starting y-coordinate of the QuadTree
        unsigned level; // the level, or depth, of the QuadTree
        vector<Node<Object> *> values; // the node values
        bool intermediate = false; // a flag indicating whether this is a QuadTree (true) or a leaf (false)
        bool hasChild = false; // a flag indicating whether this QuadTree has a child (true) or not (false)
        QuadTree * children[4];
        
    public:
        QuadTree(unsigned width, unsigned height);
        QuadTree(unsigned width, unsigned height, unsigned level);
        QuadTree(unsigned width, unsigned height, unsigned x, unsigned y, unsigned level);
        
        void insert(Node<Object> * element);
        Object get(unsigned x, unsigned y);
        void save(string name);
        
        void setWidth(unsigned width);
        unsigned getWidth();
        void setHeight(unsigned height);
        unsigned getHeight();
        void setX(unsigned x);
        unsigned getX();
        void setY(unsigned y);
        unsigned getY();
        void setLevel(unsigned level);
        unsigned getLevel();
        
        void print();

};
