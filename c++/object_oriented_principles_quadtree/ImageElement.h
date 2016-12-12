#include <string>

namespace color {
    class ImageElement {

        protected:
            string value;
        
        public:        
            virtual void setValue(string value) = 0;
            virtual string getValue() const = 0;
            
            virtual void validate(string s) = 0;
            virtual void print() = 0;
        
    };
}
