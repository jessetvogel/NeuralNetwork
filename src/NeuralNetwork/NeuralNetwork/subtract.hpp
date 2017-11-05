#ifndef subtract_hpp
#define subtract_hpp

#include "tensor.hpp"

class Subtract : Function {
    
    Variable* const a;
    Variable* const b;
    
    Subtract(Variable* a, Variable* b) : a(a), b(b) {};
    
public:
    
    template<int N> static Tensor<N>* create(Tensor<N>*, Tensor<N>*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

// Template implementations
template <int N>
Tensor<N>* Subtract::create(Tensor<N>* a, Tensor<N>* b) {
    // Make sure dimensions correspond
    for(int i = 0;i < N; ++i) {
        if(a->getDimension(i) != b->getDimension(i)) {
            Log::print("Incompatible tensors");
            return nullptr;
        }
    }
    
    // Create function object and tensor, and return
    return new Tensor<N>(new Subtract(a, b), a->getDimensions());
}

#endif

