#ifndef add_hpp
#define add_hpp

#include "tensor.hpp"

class Add : Function {
    
    Variable* const a;
    Variable* const b;
    
    Add(Variable* a, Variable* b) : a(a), b(b) {};
    
public:

    template<int N> static Tensor<N>* create(Tensor<N>*, Tensor<N>*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

// Template implementations
template <int N>
Tensor<N>* Add::create(Tensor<N>* a, Tensor<N>* b) {
    // Make sure dimensions correspond
    for(int i = 0;i < N; ++i) {
        if(a->getDimension(i) != b->getDimension(i)) {
            Log::print("Incompatible tensors");
            return nullptr;
        }
    }
    
    // Create function object and tensor, and return
    return new Tensor<N>(new Add(a, b), a->getDimensions());
}


#endif
