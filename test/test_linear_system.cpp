#include <iostream>
#include <iomanip>

#include "network.hpp"
#include "printer.hpp"

/*
 
 Solve Ax = y, with
 
     [  7 -2  3 ]       [ 1 ]
 A = [  5  1 -3 ],  y = [ 2 ]
     [  3  4 -6 ]       [ 3 ]
 
 Solution will be

     [ 5/17 ]   [ 0.29411764705 ]
 x = [ 9/17 ] = [ 0.5294117647  ]
     [   0  ]   [ 0             ]
 
 */

int main(int argc, const char * argv[]) {
    
    Network network;
    Builder* builder = network.getBuilder();
    
    Matrix* A = builder->matrix(3, 3);
    Vector* x = builder->vector(3);
    Vector* y = builder->dot(A, x);
    
    network.setOutput(y);
    network.addParameter(x);
    
    x->initializeValues(0.1);
    
    scalar* aValue = A->getValueAddr(); *aValue++ = 7.0; *aValue++ = -2.0; *aValue++ = 3.0; *aValue++ = 5.0; *aValue++ = 1.0; *aValue++ = -3.0; *aValue++ = 3.0; *aValue++ = 4.0; *aValue++ = -6.0;
    
    scalar v[9] = { 1, 2, 3 };
    Sample sample(0, 3);
    memcpy(sample.output, v, sizeof(scalar) * 3);
    std::cout << "Sample information:" << std::endl;
    Printer::printSample(sample);
    
    // Before training
    std::cout << "Initial state:" << std::endl;
    network.feed(nullptr);
    std::cout << "A = " << std::endl; Printer::print(A);
    std::cout << "x = " << std::endl; Printer::print(x);
    std::cout << "y = " << std::endl; Printer::print(y);
    
    network.feed(sample);
    std::cout << "error = " << network.getError() << std::endl << std::endl;
    
    // Train
    network.setLearningRate(0.25);
    for(int i = 0;i < 100; ++i) {
        network.train(sample);
        std::cout << "Round " << (i + 1) << ": error = " << std::setprecision(10) << network.getError() << std::endl;
    }
    
    // After training
    std::cout << std::endl << "Final state:" << std::endl;
    network.feed(nullptr);
    std::cout << "A = " << std::endl; Printer::print(A);
    std::cout << "x = " << std::endl; Printer::print(x);
    std::cout << "y = " << std::endl; Printer::print(y);
    
    std::cout << "dA = " << std::endl; Printer::print(A);
    std::cout << "dx = " << std::endl; Printer::print(x);
    std::cout << "dy = " << std::endl; Printer::print(y);
    
    std::cout << "Error = " << std::setprecision(10) << network.getError() << std::endl;
    
    return 0;
}
