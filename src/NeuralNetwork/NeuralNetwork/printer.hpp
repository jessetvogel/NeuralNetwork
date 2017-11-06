#ifndef printer_hpp
#define printer_hpp

#include <string>
#include "tensor.hpp"
#include "sample.hpp"

#define OUTPUT_STREAM std::cerr

class Printer {

public:
    
    static void print(std::string);
    
    template<int N> static void print(Tensor<N>*);
    template<int N> static void printGradient(Tensor<N>*);
    
    static void print(Sample&);
    
};

#endif
