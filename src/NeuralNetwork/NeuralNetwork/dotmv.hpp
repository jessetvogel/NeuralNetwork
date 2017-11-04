#ifndef dotmv_hpp
#define dotmv_hpp

#include "tensor.hpp"

class DotMV : Function {
    
    Variable* const a;
    Variable* const b;
    
    DotMV(Variable* a, Variable* b) : a(a), b(b) {};
    
public:
    
    template <int N, int M> static Vector<N>* create(Matrix<N, M>*, Vector<M>*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

// Template implementations
template <int N, int M>
Vector<N>* DotMV::create(Matrix<N, M>* a, Vector<M>* b) {
    // Create function object and vector, and return
    DotMV* dotMV = new DotMV(a, b);
    return new Vector<N>(dotMV);
}

#endif
