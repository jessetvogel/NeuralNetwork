#ifndef addv_hpp
#define addv_hpp

#include "math.hpp"
#include "scalar.hpp"

class SubtractS : Function {
    
    Scalar* result;
    Scalar* a;
    Scalar* b;
    
    SubtractS(Scalar*, Scalar*);
    inline ~SubtractS() {};
    
public:
    
    static Scalar* create(Scalar*, Scalar*);
    
    void evaluate();
    void backpropagate();

};

#endif

