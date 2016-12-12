#ifndef EXCEPTION
    #define EXCEPTION
    #include "Exception.h"
#endif

class InvalidInputException: public Exception {

    public:
        InvalidInputException(char character);

};
