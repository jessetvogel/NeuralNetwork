#ifndef scalar_hpp
#define scalar_hpp

#include "variable.hpp"

class Scalar : public Variable {
    
public:
    
    Scalar(Function* function) : Variable(1, function) {}
    
};

#endif
