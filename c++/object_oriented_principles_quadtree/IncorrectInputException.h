#ifndef EXCEPTION
    #define EXCEPTION
    #include "Exception.h"
#endif

class IncorrectInputException: public Exception {

    public:
        IncorrectInputException(char c);

};
