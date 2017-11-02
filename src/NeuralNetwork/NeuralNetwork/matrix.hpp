#ifndef matrix_hpp
#define matrix_hpp

#include "variable.hpp"

class Matrix : public Variable {
    
    const unsigned rowSize;
    const unsigned columnSize;
    
    /*
         Note: the values in 'value' and 'gradient' are stored as [a_00, a_01, a_02, ..., a_10, a_11, a_12, etc. ],
         that is row-major order
     */
    
public:
    
    Matrix(dimension rowSize, dimension columnSize, Function* function) : rowSize(rowSize), columnSize(columnSize), Variable(rowSize * columnSize, function) {}
    
    inline const dimension getRowSize() const { return rowSize; }
    inline const dimension getColumnSize() const { return columnSize; }
    
};

#endif
