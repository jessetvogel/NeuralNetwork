#ifndef vector_hpp
#define vector_hpp

#include "variable.hpp"

class Vector : public Variable {
    
    const unsigned int size;
    
public:
    
    Vector(unsigned int, Function*);

    inline const unsigned int getSize() const { return size; }
    
};

#endif
