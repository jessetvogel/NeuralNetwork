#ifndef dot_hpp
#define dot_hpp

#include "tensor.hpp"

class Dot : Function {
    
    Variable* const a;
    Variable* const b;
    
    template Dot(Variable* a, Variable* b) : a(a), b(b) {};
    
public:
    
    template <int...N> static Scalar* create(Tensor<N...>*, Tensor<N...>*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

// Template implementations
template <int ...N>
Scalar* Dot::create(Tensor<N...>* a, Tensor<N...>* b) {
    // Create function object and tensor, and return
    Dot* dot = new Dot(a, b);
    return new Scalar(dot);
}

#endif
