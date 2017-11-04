#ifndef builder_hpp
#define builder_hpp

#include "network.hpp"

#include "add.hpp"
#include "subtract.hpp"
#include "dot.hpp"
#include "dotmv.hpp"
#include "dotmm.hpp"
#include "sigmoid.hpp"
#include "softmax.hpp"
#include "relu.hpp"
#include "tanh.hpp"
#include "errorquadratic.hpp"
#include "errorcrossentropy.hpp"

class Builder {
    
    Network* const network;
    
    template <int ...N>
    inline Tensor<N...>* add(Tensor<N...>* tensor) {
        network->addVariable(tensor);
        return tensor;
    };
    
public:
    
    Builder(Network* network) : network(network) {}
    
    // Tensors
    inline Scalar* scalar()                                                                     { return add(new Scalar(nullptr)); }
    template <int N> inline Vector<N>* vector()                                                 { return add(new Vector<N>(nullptr)); }
    template <int N, int M> inline Matrix<N, M>* matrix()                                       { return add(new Matrix<N, M>(nullptr)); }
    template <int... N> inline Tensor<N...>* tensor()                                           { return add(new Tensor<N...>(nullptr)); }
    
    // Arithmetic
    template <int ...N> inline Tensor<N...>* add(Tensor<N...>* a, Tensor<N...>* b)              { return add(Add::create(a, b)); }
    template <int ...N> inline Tensor<N...>* subtract(Tensor<N...>* a, Tensor<N...>* b)         { return add(Subtract::create(a, b)); }
    template <int ...N> inline Scalar* inner(Tensor<N...>* a, Tensor<N...>* b)                  { return add(Dot::create(a, b)); }
    template <int N, int M> inline Vector<N>* dot(Matrix<N, M>* a, Vector<M>* b)                { return add(DotMV::create(a, b)); }
    template <int N, int M, int L> inline Matrix<N, L>* dot(Matrix<N, M>* a, Matrix<M, L>* b)   { return add(DotMM::create(a, b)); }
    
    // Activation functions
    template <int ...N> inline Tensor<N...>* sigmoid(Tensor<N...>* a)                           { return add(Sigmoid::create(a)); }
    template <int ...N> inline Tensor<N...>* reLU(Tensor<N...>* a)                              { return add(ReLU::create(a)); }
    template <int ...N> inline Tensor<N...>* tanh(Tensor<N...>* a)                              { return add(Tanh::create(a)); }
    template <int ...N> inline Tensor<N...>* softmax(Tensor<N...>* a)                           { return add(Softmax::create(a)); }
    
    // Error functions
    inline Scalar* errorQuadratic(Variable* a, Variable* b)                                     { return add(ErrorQuadratic::create(a, b)); };
    inline Scalar* errorCrossEntropy(Variable* a, Variable* b)                                  { return add(ErrorCrossEntropy::create(a, b)); };
    
};

#endif
