#ifndef addv_hpp
#define addv_hpp

#include "math.hpp"
#include "vector.hpp"

class SubtractV : Function {
    
    Vector* result;
    
    Vector* a;
    Vector* b;
    
    SubtractV(Vector*, Vector*);
    inline ~SubtractV() {};
    
public:
    
    static Vector* create(Vector*, Vector*);
    
    void evaluate();
    void backpropagate();
    
};

#endif

