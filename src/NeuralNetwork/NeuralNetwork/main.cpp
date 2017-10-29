#include <iostream>

#include "m.hpp"
#include "printer.hpp"

int main(int argc, const char * argv[]) {
    
    Vector* v = M::vector(3);
    Matrix* m = M::matrix(3, 3);
    Vector* y = M::dot(m, v);
    Scalar* s = M::dot(y, y);
    
    scalar* mValue = m->getValueAddr();
    *mValue++ = 1.0;
    *mValue++ = 2.0;
    *mValue++ = 3.0;
    *mValue++ = 4.0;
    *mValue++ = 5.0;
    *mValue++ = 6.0;
    *mValue++ = 7.0;
    *mValue++ = 8.0;
    *mValue++ = 9.0;
    
    scalar* vValue = v->getValueAddr();
    *vValue++ = 1.0;
    *vValue++ = 2.0;
    *vValue++ = 3.0;
    
    s->computeValue();

    Printer::printMatrix(m);
    Printer::printVector(v);
    Printer::printVector(y);
    Printer::printScalar(s);
    
    return 0;
}
