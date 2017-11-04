#ifndef softmax_hpp
#define softmax_hpp

#include "tensor.hpp"

class Softmax : Function {
    
    Variable* const a;
    
    Softmax(Variable* a) : a(a) {};
    
public:
    
    template <int ...N> static Tensor<N...>* create(Tensor<N...>*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

// Template implementations
template <int ...N>
Tensor<N...>* Softmax::create(Tensor<N...>* a) {
    // Create function object and tensor, and return
    Softmax* softmax = new Softmax(a);
    return new Tensor<N...>(softmax);
}

#endif

