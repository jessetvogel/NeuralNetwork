#ifndef errorcrossentropy_hpp
#define errorcrossentropy_hpp

#include "scalar.hpp"
#include "vector.hpp"
#include "matrix.hpp"

class ErrorCrossEntropy : Function {
    
    Variable* const exact;
    Variable* const estimate;
    
    ErrorCrossEntropy(Variable* exact, Variable* estimate) : exact(exact), estimate(estimate) {};
    
public:
    
    static Scalar* create(Variable*, Variable*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
public:
    
    
};

#endif
