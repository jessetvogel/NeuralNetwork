#ifndef addv_hpp
#define addv_hpp

#include "math.hpp"
#include "scalar.hpp"

class AddS : Function {
    
    Scalar* result;
    Scalar* a;
    Scalar* b;
    
    AddS(Scalar*, Scalar*);
    inline ~AddS() {};
    
public:
    
    static Scalar* create(Scalar*, Scalar*);
    
    void evaluate();
    void backpropagate();
    
};

#endif
