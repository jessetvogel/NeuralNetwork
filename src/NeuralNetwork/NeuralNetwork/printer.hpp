#ifndef printer_hpp
#define printer_hpp

#include "tensor.hpp"
#include "sample.hpp"

#define OUTPUT_STREAM std::cerr

class Printer {

public:
    
    template<int... N> static void print(Tensor<N...>*);
    template<int... N> static void printGradient(Tensor<N...>*);
    
    static void printSample(Sample&);
    
};

// Template implementation
#include <iostream>

template <int ...N>
void Printer::print(Tensor<N...>* tensor) {
    scalar* value = tensor->getValueAddr();
    switch(tensor->getOrder()) {
        case 0: {
            // Scalars
            OUTPUT_STREAM << "[" << *value << "]" << std::endl << std::endl;
            break;
        }
            
        case 1: {
            // Vectors
            dimension n = tensor->getSize();
            OUTPUT_STREAM << "[ ";
            for(dimension i = 0;i < n; ++i) {
                OUTPUT_STREAM << (*(value++));
                if(i < n - 1) OUTPUT_STREAM << ", ";
            }
            OUTPUT_STREAM << " ]" << std::endl << std::endl;
            break;
        }
            
        case 2: {
            // Matrices
            dimension rows = tensor->getDimension(MATRIX_ROWS);
            dimension columns = tensor->getDimension(MATRIX_COLUMNS);
            for(dimension i = 0;i < rows; ++i) {
                OUTPUT_STREAM << "[ ";
                for(dimension j = 0;j < columns; ++j) {
                    OUTPUT_STREAM << (*(value++));
                    if(j < columns - 1) OUTPUT_STREAM << ", ";
                }
                OUTPUT_STREAM << " ]" << std::endl;
            }
            OUTPUT_STREAM << std::endl;
            break;
        }
            
        default: {
            OUTPUT_STREAM << "Print function for tensors of order " << tensor->getOrder() << std::endl;
            break;
        }
    }
}

#endif
