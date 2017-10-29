#ifndef sigmoid_hpp
#define sigmoid_hpp

#include "scalar.hpp"
#include "vector.hpp"
#include "matrix.hpp"

class Sigmoid : Function {
        
    Variable* const a;
        
    Sigmoid(Variable* a) : a(a) {};
    
    scalar sig(scalar);
    
public:
        
    static Scalar* create(Scalar*);
    static Vector* create(Vector*);
    static Matrix* create(Matrix*);

    void setResult(Variable*);
    void evaluate();
    void backpropagate();

};

#endif
