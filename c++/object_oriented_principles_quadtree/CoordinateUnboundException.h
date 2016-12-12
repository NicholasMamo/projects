#ifndef EXCEPTION
    #define EXCEPTION
    #include "Exception.h"
#endif

class CoordinateUnboundException: public Exception {

    public:
        CoordinateUnboundException(unsigned x, unsigned y);

};
