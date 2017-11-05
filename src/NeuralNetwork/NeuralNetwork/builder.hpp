#ifndef builder_hpp
#define builder_hpp

#include "network.hpp"

#include "add.hpp"
#include "subtract.hpp"
#include "dot.hpp"
#include "dotmv.hpp"
#include "dotmm.hpp"
#include "convolution.hpp"
#include "maxpool.hpp"
#include "sigmoid.hpp"
#include "softmax.hpp"
#include "relu.hpp"
#include "tanh.hpp"
#include "errorquadratic.hpp"
#include "errorcrossentropy.hpp"

class Builder {
    
    Network* const network;
    
    template <int N>
    inline Tensor<N>* add(Tensor<N>* tensor) {
        network->addVariable(tensor);
        return tensor;
    };
    
public:
    
    Builder(Network* network) : network(network) {}
    
    // Standard types
    template <int N> inline Tensor<N>* tensor(dim* dimensions)                                  { return add(new Tensor<N>(nullptr, dimensions)); }
    inline Scalar* scalar()                                                                     { return add(new Scalar(nullptr)); }
    inline Vector* vector(dim length)                                                           { return add(new Vector(nullptr, &length)); }
    inline Matrix* matrix(dim rows, dim columns)                                                { dim dimensions[2] = { rows, columns}; return add(new Matrix(nullptr, dimensions)); }

    // Convolutional types
    inline Volume* volume(dim width, dim height, dim depth)                                     { dim dimensions[3] = { width, height, depth }; return add(new Volume(nullptr, dimensions)); }
    inline FilterSet* filterset(dim width, dim height, dim depth, dim amount)                   { dim dimensions[4] = { width, height, depth, amount }; return add(new FilterSet(nullptr, dimensions)); }

    // Activation functions
    template <int N> inline Tensor<N>* sigmoid(Tensor<N>* a)                                    { return add(Sigmoid::create(a)); }
    template <int N> inline Tensor<N>* reLU(Tensor<N>* a)                                       { return add(ReLU::create(a)); }
    template <int N> inline Tensor<N>* tanh(Tensor<N>* a)                                       { return add(Tanh::create(a)); }
    template <int N> inline Tensor<N>* softmax(Tensor<N>* a)                                    { return add(Softmax::create(a)); }
    
    // Error functions
    inline Scalar* errorQuadratic(Variable* a, Variable* b)                                     { return add(ErrorQuadratic::create(a, b)); };
    inline Scalar* errorCrossEntropy(Variable* a, Variable* b)                                  { return add(ErrorCrossEntropy::create(a, b)); };
    
    // Arithmetic
    template <int N> inline Tensor<N>* add(Tensor<N>* a, Tensor<N>* b)                          { return add(Add::create(a, b)); }
    template <int N> inline Tensor<N>* subtract(Tensor<N>* a, Tensor<N>* b)                     { return add(Subtract::create(a, b)); }
    template <int N> inline Scalar* inner(Tensor<N>* a, Tensor<N>* b)                           { return add(Dot::create(a, b)); }
    inline Vector* dot(Matrix* a, Vector* b)                                                    { return add(DotMV::create(a, b)); }
    inline Matrix* dot(Matrix* a, Matrix* b)                                                    { return add(DotMM::create(a, b)); }
    
    // Convolutional functions
    inline Volume* convolution(Volume* a, FilterSet* b)                                         { return add(Convolution::create(a, b)); }
    inline Volume* maxpool(Volume* a, int w, int h)                                             { return add(MaxPool::create(a, w, h)); }
    
};

#endif
