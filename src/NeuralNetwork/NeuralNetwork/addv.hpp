#ifndef addv_hpp
#define addv_hpp

#include "math.hpp"
#include "vector.hpp"

class AddV : Function {
    
    Vector* result;
    
    Vector* a;
    Vector* b;
    
    AddV(Vector*, Vector*);
    inline ~AddV() {};
    
public:
    
    static Vector* create(Vector*, Vector*);
    
    void evaluate();
    void backpropagate();
    
};

#endif
