#ifndef vector_hpp
#define vector_hpp

#include "variable.hpp"

class Vector : public Variable {
    
public:
    
    Vector(dimension size, Function* function) : Variable(size, function) {}
    
};

#endif
