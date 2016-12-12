#ifndef EXCEPTION
    #define EXCEPTION
    #include "Exception.h"
#endif

/**
 * Get the message produced by the Exception
 * return - the message produced by the Exception
 */
string Exception::getMessage() {
    return this->message;
}
