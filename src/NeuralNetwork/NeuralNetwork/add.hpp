#ifndef add_hpp
#define add_hpp

#include "tensor.hpp"

class Add : Function {
    
    Variable* const a;
    Variable* const b;
    
    Add(Variable* a, Variable* b) : a(a), b(b) {};
    
public:

    template<int ...N> static Tensor<N...>* create(Tensor<N...>*, Tensor<N...>*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

// Template implementations
template <int ...N>
Tensor<N...>* Add::create(Tensor<N...>* a, Tensor<N...>* b) {
    // Create function object and tensor, and return
    Add* add = new Add(a, b);
    return new Tensor<N...>(add);
}


#endif
