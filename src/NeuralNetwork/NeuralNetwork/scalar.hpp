#ifndef scalar_hpp
#define scalar_hpp

#include "math.hpp"

class Scalar {
    
    const Function* function;
    
    scalar value;
    scalar gradient;
    
    bool computedValue;
    bool computedGradient;
    
public:
    
    Scalar(Function*);
    ~Scalar();
    
    inline scalar* getValueAddr() { return &value; }
    inline scalar* getGradientAddr() { return &gradient; }
    inline const Function* getFunction() const { return function; }
    
    inline void computeValue() { if(computedValue) return; computedValue = true; function->evaluate(); };
    inline void computeGradient() { if(computedGradient) return; computedGradient = true; function->backpropagate(); };
    
    void findGradients(); // Such a function (maybe another name) can only be called on scalars. This will cause a chain reaction (pun intended) of computing gradients (reverse mode differentiation).
    
};

#endif
