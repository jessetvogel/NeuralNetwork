#ifndef tanh_hpp
#define tanh_hpp

#include "tensor.hpp"

class Tanh : Function {
    
    Variable* const a;
    
    Tanh(Variable* a) : a(a) {};
    
public:
    
    template <int N> static Tensor<N>* create(Tensor<N>* a) { return new Tensor<N>(new Tanh(a), a->getDimensions()); };
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif
