#ifndef math_h
#define math_h

#include "log.hpp" // TODO: remove this

typedef double scalar;

class Function {
    
public:
    
    inline virtual ~Function() {}

    inline virtual void evaluate() const {}
    inline virtual void backpropagate() const {}

};

#endif
