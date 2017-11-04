#ifndef sigmoid_hpp
#define sigmoid_hpp

#include "tensor.hpp"

class Sigmoid : Function {
        
    Variable* const a;
        
    Sigmoid(Variable* a) : a(a) {};
    
    scalar sig(scalar);
    
public:
        
    template <int N> static Tensor<N>* create(Tensor<N>*);

    void setResult(Variable*);
    void evaluate();
    void backpropagate();

};

// Template implementations
template <int N>
Tensor<N>* Sigmoid::create(Tensor<N>* a) {
    // Create function object and tensor, and return
    Sigmoid* sigmoid = new Sigmoid(a);
    return new Tensor<N>(sigmoid);
}

#endif
