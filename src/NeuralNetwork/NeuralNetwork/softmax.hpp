#ifndef softmax_hpp
#define softmax_hpp

#include "vector.hpp"

class Softmax : Function {
    
    Variable* const a;
    
    Softmax(Variable* a) : a(a) {};
    
public:
    
    static Vector* create(Vector*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif

