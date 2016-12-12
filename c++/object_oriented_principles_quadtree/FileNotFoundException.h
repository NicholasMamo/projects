#ifndef EXCEPTION
    #define EXCEPTION
    #include "Exception.h"
#endif

class FileNotFoundException: public Exception {

    public:
        FileNotFoundException(string filename);

};
