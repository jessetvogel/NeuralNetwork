#ifndef softmax_hpp
#define softmax_hpp

#include "scalar.hpp"
#include "vector.hpp"
#include "matrix.hpp"

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

