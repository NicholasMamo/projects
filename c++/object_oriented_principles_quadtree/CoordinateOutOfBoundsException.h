#ifndef EXCEPTION
    #define EXCEPTION
    #include "Exception.h"
#endif

class CoordinateOutOfBoundsException: public Exception {

    public:
        CoordinateOutOfBoundsException(unsigned x, unsigned y);

};
