#ifndef tensor_hpp
#define tensor_hpp

#include "variable.hpp"

template <int N>
class Tensor : public Variable {
    
    dim dimensions[N];
    
public:
    
    Tensor(Function* function, dim* d) : Variable(function) {
        // Store dimensions
        size = 1;
        for(int i = 0;i < N; ++i)
            size *= dimensions[i] = d[i];
        value = new scalar[size];
        gradient = new scalar[size];

    };
    
    inline dim* getDimensions() { return dimensions; }
    inline dim getDimension(int n) { return dimensions[n]; }
    
};

// Specialization implementations
template <>
class Tensor<0> : public Variable {
    
public:
    
    Tensor(Function* function) : Variable(function) {
        size = 1;
        value = new scalar[size];
        gradient = new scalar[size];
    }
    
    Tensor(Function* function, dim*) : Tensor(function) {}
    Tensor() : Tensor(nullptr) {}
    
    inline dim* getDimensions() { return nullptr; }
    inline dim getDimension(int) { return 0; }
    
};

#include "types.hpp"

#endif
