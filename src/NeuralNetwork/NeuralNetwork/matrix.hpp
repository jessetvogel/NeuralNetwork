#ifndef matrix_hpp
#define matrix_hpp

#include "math.hpp"

class Matrix {
    
    const unsigned rowSize;
    const unsigned columnSize;
    
    const Function* function;
    
    scalar* value;
    scalar* gradient;
    
    /*
     
         Note: the values in 'value' and 'gradient' are stored as [a_00, a_01, a_02, ..., a_10, a_11, a_12, etc. ]
     
     */
    
    bool computedValue;
    bool computedGradient;
    
public:
    
    Matrix(unsigned int, unsigned int, Function*);
    ~Matrix();
    
    inline const unsigned int getRowSize() const { return rowSize; }
    inline const unsigned int getColumnSize() const { return columnSize; }

    inline scalar* getValueAddr() const { return value; }
    inline scalar* getGradientAddr() const { return gradient; }
    inline const Function* getFunction() const { return function; }
    
    inline void computeValue() { if(computedValue) return; computedValue = true; function->evaluate(); };
    inline void computeGradient() { if(computedGradient) return; computedGradient = true; function->backpropagate(); };
    
};

#endif
