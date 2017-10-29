#ifndef subtract_hpp
#define subtract_hpp

#include "scalar.hpp"
#include "vector.hpp"
#include "matrix.hpp"

class Subtract : Function {
    
    Variable* const a;
    Variable* const b;
    
    Subtract(Variable* a, Variable* b) : a(a), b(b) {};
    
public:
    
    static Scalar* create(Scalar*, Scalar*);
    static Vector* create(Vector*, Vector*);
    static Matrix* create(Matrix*, Matrix*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif

