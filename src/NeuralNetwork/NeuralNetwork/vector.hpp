#ifndef vector_hpp
#define vector_hpp

#include "math.hpp"

class Vector {
    
    const unsigned int size;
    
    const Function* function;
    
    scalar* value;
    scalar* gradient;
    
    bool computedValue;
    bool computedGradient;
    
public:
    
    Vector(unsigned int, Function*);
    ~Vector();

    inline const unsigned int getSize() const { return size; }
    
    inline scalar* getValueAddr() const { return value; }
    inline scalar* getGradientAddr() const { return gradient; }
    inline const Function* getFunction() const { return function; }
    
    inline void computeValue() { if(computedValue) return; computedValue = true; function->evaluate(); };
    inline void computeGradient() { if(computedGradient) return; computedGradient = true; function->backpropagate(); };
    
};

#endif
