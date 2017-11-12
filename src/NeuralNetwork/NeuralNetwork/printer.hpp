#ifndef printer_hpp
#define printer_hpp

#include <string>
#include "tensor.hpp"
#include "sample.hpp"

#define OUTPUT_STREAM std::cerr

class Printer {

    template<int N> static void print(Tensor<N>*, scalar*);
    
public:
    
    static void print(std::string);
    
    template<int N> static void print(Tensor<N>* tensor) {
        print(tensor, tensor->getValueAddr());
    };
    
    template<int N> static void printGradient(Tensor<N>* tensor) {
        print(tensor, tensor->getGradientAddr());
    };
    
    static void print(Sample&);
    
};

#endif
