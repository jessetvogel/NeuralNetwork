#ifndef math_h
#define math_h

#include "log.hpp" // TODO: remove this

#include <cstdint>

typedef double scalar; // TODO: guaranteed to be 8 bytes?
typedef uint32_t dimension;

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
