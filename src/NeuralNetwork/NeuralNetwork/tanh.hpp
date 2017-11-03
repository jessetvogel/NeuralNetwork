#ifndef tanh_hpp
#define tanh_hpp

#include "scalar.hpp"
#include "vector.hpp"
#include "matrix.hpp"

class Tanh : Function {
    
    Variable* const a;
    
    Tanh(Variable* a) : a(a) {};
    
public:
    
    static Scalar* create(Scalar*);
    static Vector* create(Vector*);
    static Matrix* create(Matrix*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif
