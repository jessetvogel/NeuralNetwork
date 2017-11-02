#ifndef relu_hpp
#define relu_hpp

#include "scalar.hpp"
#include "vector.hpp"
#include "matrix.hpp"

class ReLU : Function {
    
    Variable* const a;
    
    ReLU(Variable* a) : a(a) {};
    
public:
    
    static Scalar* create(Scalar*);
    static Vector* create(Vector*);
    static Matrix* create(Matrix*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif
