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

// Specializations implementations
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

template <>
class Tensor<1> : public Variable {
    
    dim length;
    
public:
    
    Tensor(Function* function, dim* d) : Variable(function) {
        this->length = d[0];
        size = length;
        value = new scalar[size];
        gradient = new scalar[size];
    }
    
    inline dim* getDimensions() { return &length; }
    inline dim getDimension(int) { return length; }
    inline dim getLength() { return length; }
    
};

template <>
class Tensor<2> : public Variable {
    
    dim dimensions[2];
    
public:
    
    Tensor(Function* function, dim* d) : Variable(function) {
        size = (dimensions[0] = d[0]) * (dimensions[1] = d[1]);
        value = new scalar[size];
        gradient = new scalar[size];
    }
    
    inline dim* getDimensions() { return dimensions; }
    inline dim getDimension(int n) { return dimensions[n]; }
    inline dim getRowLength() { return dimensions[0]; }
    inline dim getColumnLength() { return dimensions[1]; }
    
};

// Define some types
typedef Tensor<0> Scalar;
typedef Tensor<1> Vector;
typedef Tensor<2> Matrix;

#endif
