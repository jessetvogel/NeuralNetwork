#ifndef dotmm_hpp
#define dotmm_hpp

#include "tensor.hpp"

class DotMM : Function {
    
    Variable* const a;
    Variable* const b;
    
    DotMM(Variable* a, Variable* b) : a(a), b(b) {};
    
public:
    
    template <int N, int M, int L> static Matrix<N, L>* create(Matrix<N, M>*, Matrix<M, L>*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

// Template implementations
template <int N, int M, int L>
Matrix<N, L>* DotMM::create(Matrix<N, M>* a, Matrix<M, L>* b) {
    // Create function object and vector, and return
    DotMM* dotMM = new DotMM(a, b);
    return new Matrix<N, L>(dotMM);
}

#endif
