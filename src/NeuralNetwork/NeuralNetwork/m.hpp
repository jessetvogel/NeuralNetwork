#ifndef m_hpp
#define m_hpp

#include "add.hpp"
#include "subtract.hpp"
#include "dotvv.hpp"
#include "dotmv.hpp"
#include "sigmoid.hpp"
#include "softmax.hpp"

class M {
    
public:
    
    inline static Scalar* add(Scalar* a, Scalar* b) { return Add::create(a, b); }
    inline static Vector* add(Vector* a, Vector* b) { return Add::create(a, b); }
    inline static Matrix* add(Matrix* a, Matrix* b) { return Add::create(a, b); }
    
    inline static Scalar* subtract(Scalar* a, Scalar* b) { return Subtract::create(a, b); }
    inline static Vector* subtract(Vector* a, Vector* b) { return Subtract::create(a, b); }
    inline static Matrix* subtract(Matrix* a, Matrix* b) { return Subtract::create(a, b); }
    
    inline static Scalar* dot(Vector* a, Vector* b) { return DotVV::create(a, b); }
    inline static Vector* dot(Matrix* a, Vector* b) { return DotMV::create(a, b); }
    
    inline static Scalar* sigmoid(Scalar* a) { return Sigmoid::create(a); }
    inline static Vector* sigmoid(Vector* a) { return Sigmoid::create(a); }
    inline static Matrix* sigmoid(Matrix* a) { return Sigmoid::create(a); }
    
//    inline static Scalar* softmax(Scalar* a) { return Softmax::create(a); }
    inline static Vector* softmax(Vector* a) { return Softmax::create(a); }
//    inline static Matrix* softmax(Matrix* a) { return Softmax::create(a); }

};

#endif
