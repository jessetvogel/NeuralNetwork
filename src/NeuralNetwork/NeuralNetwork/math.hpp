#ifndef math_h
#define math_h

#include "log.hpp" // TODO: remove this

typedef double scalar;

class Variable;

class Function {
    
protected:
    
    Variable* result;
    
public:
    
    virtual ~Function() {};

    virtual void setResult(Variable*) = 0;
    virtual void evaluate() = 0;
    virtual void backpropagate() = 0;
    
};

#endif
