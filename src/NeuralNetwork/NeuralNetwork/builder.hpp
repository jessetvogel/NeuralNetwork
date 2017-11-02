#ifndef builder_hpp
#define builder_hpp

#include "network.hpp"

#include "add.hpp"
#include "subtract.hpp"
#include "dotvv.hpp"
#include "dotmv.hpp"
#include "dotmm.hpp"
#include "sigmoid.hpp"
#include "softmax.hpp"
#include "relu.hpp"
#include "errorquadratic.hpp"

class Builder {
    
    Network* const network;
    
    inline Scalar* addScalar(Scalar* s) { network->addVariable(s); return s; };
    inline Vector* addVector(Vector* v) { network->addVariable(v); return v; };
    inline Matrix* addMatrix(Matrix* m) { network->addVariable(m); return m; };
    
public:
    
    Builder(Network* network) : network(network) {}
    
    inline Scalar* scalar()                                 { return addScalar(new Scalar(nullptr)); }
    inline Vector* vector(dimension n)                      { return addVector(new Vector(n, nullptr)); }
    inline Matrix* matrix(dimension i, dimension j)         { return addMatrix(new Matrix(i, j, nullptr)); }
    
    inline Scalar* add(Scalar* a, Scalar* b)                { return addScalar(Add::create(a, b)); }
    inline Vector* add(Vector* a, Vector* b)                { return addVector(Add::create(a, b)); }
    inline Matrix* add(Matrix* a, Matrix* b)                { return addMatrix(Add::create(a, b)); }
    
    inline Scalar* subtract(Scalar* a, Scalar* b)           { return addScalar(Subtract::create(a, b)); }
    inline Vector* subtract(Vector* a, Vector* b)           { return addVector(Subtract::create(a, b)); }
    inline Matrix* subtract(Matrix* a, Matrix* b)           { return addMatrix(Subtract::create(a, b)); }
    
    inline Scalar* dot(Vector* a, Vector* b)                { return addScalar(DotVV::create(a, b)); }
    inline Vector* dot(Matrix* a, Vector* b)                { return addVector(DotMV::create(a, b)); }
    inline Matrix* dot(Matrix* a, Matrix* b)                { return addMatrix(DotMM::create(a, b)); }
    
    inline Scalar* sigmoid(Scalar* a)                       { return addScalar(Sigmoid::create(a)); }
    inline Vector* sigmoid(Vector* a)                       { return addVector(Sigmoid::create(a)); }
    inline Matrix* sigmoid(Matrix* a)                       { return addMatrix(Sigmoid::create(a)); }
    
    inline Scalar* reLU(Scalar* a)                          { return addScalar(ReLU::create(a)); }
    inline Vector* reLU(Vector* a)                          { return addVector(ReLU::create(a)); }
    inline Matrix* reLU(Matrix* a)                          { return addMatrix(ReLU::create(a)); }
    
//    inline Scalar* softmax(Scalar* a)                       { return addScalar(Softmax::create(a)); }
    inline Vector* softmax(Vector* a)                       { return addVector(Softmax::create(a)); }
//    inline Matrix* softmax(Matrix* a)                       { return addMatrix(Softmax::create(a)); }
    
    inline Scalar* errorQuadratic(Variable* a, Variable* b) { return addScalar(ErrorQuadratic::create(a, b)); };
    
};

#endif
