#ifndef softmax_hpp
#define softmax_hpp

#include "tensor.hpp"

class Softmax : Function {
    
    Vector* const a;
    
    Softmax(Vector* a) : a(a) {};
    
public:
    
    inline static Vector* create(Vector* a) { return new Vector(new Softmax(a), a->getDimensions()); }
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif

