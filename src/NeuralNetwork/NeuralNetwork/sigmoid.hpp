#ifndef sigmoid_hpp
#define sigmoid_hpp

#include "vector.hpp"

class Sigmoid : Function {
    
    Vector* result;
        
    Vector* a;
        
    Sigmoid(Vector*);
    inline ~Sigmoid() {};
    
    scalar f(scalar);
    
public:
        
    static Vector* create(Vector*);
        
    void evaluate();

};

#endif
