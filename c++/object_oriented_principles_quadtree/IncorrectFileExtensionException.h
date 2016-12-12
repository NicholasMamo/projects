#ifndef EXCEPTION
    #define EXCEPTION
    #include "Exception.h"
#endif

class IncorrectFileExtensionException: public Exception {

    public:
        IncorrectFileExtensionException(string extension);

};
