#ifndef add_hpp
#define add_hpp

#include "scalar.hpp"
#include "vector.hpp"
#include "matrix.hpp"

class Add : Function {
    
    Variable* const a;
    Variable* const b;
    
    Add(Variable* a, Variable* b) : a(a), b(b) {};
    
public:

    static Scalar* create(Scalar*, Scalar*);
    static Vector* create(Vector*, Vector*);
    static Matrix* create(Matrix*, Matrix*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif
