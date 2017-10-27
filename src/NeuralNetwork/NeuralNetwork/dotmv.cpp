#include "dotmv.hpp"

DotMV::DotMV(Matrix* a, Vector* b) : a(a), b(b) {}

Vector* DotMV::create(Matrix* a, Vector* b) {
    // Make sure the number of columns matches the size of the vector
    if(a->getColumnSize() != b->getSize()) {
        Log::print("Matrix and vector are incompatible");
        return nullptr;
    }
    
    // Create function object and vector, and return
    DotMV* dotMV = new DotMV(a, b);
    return (dotMV->result = new Vector(a->getRowSize(), dotMV));
}

void DotMV::evaluate() {
    // Computes product between matrix a and vector b
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    scalar* valueB;
    
    const unsigned int rows = a->getRowSize();
    const unsigned int columns = a->getColumnSize();
    for(unsigned int i = 0;i < rows; ++i) {
        // Compute inner product of i'th row of the matrix with vector
        scalar value = 0.0;
        valueB = b->getValueAddr();
        for(unsigned int j = 0;j < columns; ++j)
            value += (*(valueA++)) * (*(valueB++));
        
        // Store result
        *(valueResult++) = value;
    }
}
