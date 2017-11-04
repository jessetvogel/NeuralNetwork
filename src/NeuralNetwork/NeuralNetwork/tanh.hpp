#ifndef tanh_hpp
#define tanh_hpp

#include "tensor.hpp"

class Tanh : Function {
    
    Variable* const a;
    
    Tanh(Variable* a) : a(a) {};
    
public:
    
    template <int N> static Tensor<N>* create(Tensor<N>*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

// Template implementations
template <int N>
Tensor<N>* Tanh::create(Tensor<N>* a) {
    // Create function object and tensor, and return
    Tanh* tanh = new Tanh(a);
    return new Tensor<N>(tanh);
}

#endif
