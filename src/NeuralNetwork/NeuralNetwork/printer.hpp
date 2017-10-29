#ifndef printer_hpp
#define printer_hpp

#include "scalar.hpp"
#include "vector.hpp"
#include "matrix.hpp"

class Printer {

public:
    
    static void printScalar(Scalar*);
    static void printVector(Vector*);
    static void printMatrix(Matrix*);
    
};

#endif
