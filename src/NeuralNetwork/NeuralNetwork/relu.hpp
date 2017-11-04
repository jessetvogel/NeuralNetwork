#ifndef relu_hpp
#define relu_hpp

#include "tensor.hpp"

class ReLU : Function {
    
    Variable* const a;
    
    ReLU(Variable* a) : a(a) {};
    
public:
    
    template <int ...N> static Tensor<N...>* create(Tensor<N...>*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

// Template implementations
template <int... N>
Tensor<N...>* ReLU::create(Tensor<N...>* a) {
    // Create function object and tensor, and return
    ReLU* reLU = new ReLU(a);
    return new Tensor<N...>(reLU);
}

#endif
