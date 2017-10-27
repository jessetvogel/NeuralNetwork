#ifndef dotmv_hpp
#define dotmv_hpp

#include "vector.hpp"
#include "matrix.hpp"

class DotMV : Function {
    
    Vector* result;
    
    Matrix* a;
    Vector* b;
    
    DotMV(Matrix*, Vector*);
    inline ~DotMV() {};
    
public:
    
    static Vector* create(Matrix*, Vector*);
    
    void evaluate();
    void backpropagate();
    
};

#endif
