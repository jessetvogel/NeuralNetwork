#ifndef dotmv_hpp
#define dotmv_hpp

#include "tensor.hpp"

class DotMV : Function {
    
    Matrix* const a;
    Vector* const b;
    
    DotMV(Matrix* a, Vector* b) : a(a), b(b) {};
    
public:
    
    static Vector* create(Matrix*, Vector*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif
