#ifndef addm_hpp
#define addm_hpp

#include "math.hpp"
#include "matrix.hpp"

class AddM : Function {
    
    Matrix* result;
    
    Matrix* a;
    Matrix* b;
    
    AddM(Matrix*, Matrix*);
    inline ~AddM() {};
    
public:
    
    static Matrix* create(Matrix*, Matrix*);
    
    void evaluate();
    void backpropagate();

};

#endif

