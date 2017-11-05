#ifndef relu_hpp
#define relu_hpp

#include "tensor.hpp"

class ReLU : Function {
    
    Variable* const a;
    
    ReLU(Variable* a) : a(a) {};
    
public:
    
    template <int N> static Tensor<N>* create(Tensor<N>* a) { return new Tensor<N>(new ReLU(a), a->getDimensions()); };
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif
