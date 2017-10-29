#ifndef dotvv_hpp
#define dotvv_hpp

#include "scalar.hpp"
#include "vector.hpp"

class DotVV : Function {
    
    Vector* const a;
    Vector* const b;
    
    DotVV(Vector* a, Vector* b) : a(a), b(b) {};
    
public:
    
    static Scalar* create(Vector*, Vector*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif
