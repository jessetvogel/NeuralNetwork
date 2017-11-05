#ifndef sigmoid_hpp
#define sigmoid_hpp

#include "tensor.hpp"

class Sigmoid : Function {
        
    Variable* const a;
        
    Sigmoid(Variable* a) : a(a) {};
    
    scalar sig(scalar);
    
public:
        
    template <int N> inline static Tensor<N>* create(Tensor<N>* a) { return new Tensor<N>(new Sigmoid(a), a->getDimensions()); };

    void setResult(Variable*);
    void evaluate();
    void backpropagate();

};

#endif
