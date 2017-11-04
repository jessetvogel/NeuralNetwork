#ifndef subtract_hpp
#define subtract_hpp

#include "tensor.hpp"

class Subtract : Function {
    
    Variable* const a;
    Variable* const b;
    
    Subtract(Variable* a, Variable* b) : a(a), b(b) {};
    
public:
    
    template <int ...N> static Tensor<N...>* create(Tensor<N...>*, Tensor<N...>*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

// Template implementations
template <int ...N>
Tensor<N...>* Subtract::create(Tensor<N...>* a, Tensor<N...>* b) {
    // Create function object and tensor, and return
    Subtract* subtract = new Subtract(a, b);
    return new Scalar(subtract);
}

#endif

