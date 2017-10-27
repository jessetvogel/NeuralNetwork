#ifndef dotvv_hpp
#define dotvv_hpp

#include "scalar.hpp"
#include "vector.hpp"

class DotVV : Function {
    
    Scalar* result;
    
    Vector* a;
    Vector* b;
    
    DotVV(Vector*, Vector*);
    inline ~DotVV() {};
    
public:
    
    static Scalar* create(Vector*, Vector*);
    
    void evaluate();
    void backpropagate();
    
};

#endif
