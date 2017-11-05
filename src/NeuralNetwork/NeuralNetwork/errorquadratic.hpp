#ifndef errorquadratic_hpp
#define errorquadratic_hpp

#include "tensor.hpp"

class ErrorQuadratic : Function {
   
    Variable* const exact;
    Variable* const estimate;
    
    ErrorQuadratic(Variable* exact, Variable* estimate) : exact(exact), estimate(estimate) {};
    
public:
    
    static Scalar* create(Variable*, Variable*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif
