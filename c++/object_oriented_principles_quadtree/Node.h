template <class Object>
class Node {

    private:
        unsigned x;
        unsigned y;
        Object value;
        
    public:
        Node();
        Node(unsigned x, unsigned y, Object value);
        
        void setX(unsigned x);
        unsigned getX();
        void setY(unsigned y);
        unsigned getY();
        void setValue(Object value);
        Object getValue();
        
        void print();

};
