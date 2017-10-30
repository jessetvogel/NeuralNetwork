#ifndef printer_hpp
#define printer_hpp

#include "scalar.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "sample.hpp"

class Printer {

public:
    
    static void printScalar(Scalar*);
    static void printVector(Vector*);
    static void printMatrix(Matrix*);
    
    static void printScalarGradient(Scalar*);
    static void printVectorGradient(Vector*);
    static void printMatrixGradient(Matrix*);
    
    static void printSample(Sample&);
    
};

#endif
