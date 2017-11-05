#ifndef printer_hpp
#define printer_hpp

#include "tensor.hpp"
#include "sample.hpp"

#define OUTPUT_STREAM std::cerr

class Printer {

public:
    
    template<int N> static void print(Tensor<N>*);
    template<int N> static void printGradient(Tensor<N>*);
    
    static void printSample(Sample&);
    
};

#endif
