#ifndef tensor_hpp
#define tensor_hpp

#include "variable.hpp"

template <int... N>
class Tensor : public Variable {
    
    dimension dimensions[sizeof...(N)];
    
public:
    
    Tensor(Function* function);
    Tensor() : Tensor(nullptr) {};
    ~Tensor();
    
    
    inline dimension getOrder() { return sizeof...(N); }
    inline dimension getDimension(int n) { return dimensions[n]; }
    
    bool sameType(Variable* other) {
        if(other->getOrder() != sizeof...(N)) return false;
        for(int i = 0;i < sizeof...(N); ++i)
            if(other->getDimension(i) != dimensions[i]) return false;
        return true;
    };
    
};

// Define some types
typedef Tensor<> Scalar;
template <int N> using Vector = Tensor<N>;
template <int N, int M> using Matrix = Tensor<N, M>;

#define MATRIX_ROWS (0)
#define MATRIX_COLUMNS (1)

// Template implementations
template <int... N>
Tensor<N...>::Tensor(Function* function) : dimensions{ N... }, Variable(function) {
    // Compute size TODO: not sure why this can't be moved to tensor.cpp, but for some reason it won't compile then
    size = 1;
    for(int i = 0;i < sizeof...(N); ++i)
        size *= dimensions[i];
    
    // Allocate memory
    value = new scalar[size];
    gradient = new scalar[size];
    
    // Set dim
    dim = dimensions;
};

#endif
