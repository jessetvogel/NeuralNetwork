#include <iostream>
#include <iomanip>

#include "network.hpp"
#include "printer.hpp"

/*
 
 Determines the inverse of some matrix A
 
 Network has form A * B = I, so that B will be the inverse of A
 
 We should find
 
          [ -2    8  -5 ]
 inv(A) = [  3  -11   7 ]
          [  9  -34  21 ]
 
 */

int main(int argc, const char * argv[]) {
    // Create network
    Network network;
    
    Builder* b = network.getBuilder();
    
    auto A = b->matrix(3, 3);
    auto B = b->matrix(3, 3);
    auto I = b->dot(A, B);
    
    network.addParameter(B);
    network.setOutput(I);
    
    // Set values
    B->initializeValues(0.1);
    
    scalar a[9] = {
        7.0, 2.0, 1.0,
        0.0, 3.0, -1.0,
        -3.0, 4.0, -2.0
    };
    memcpy(A->getValueAddr(), a, sizeof(scalar) * A->getSize());
    
    Sample sample(0, 9);
    scalar identity[9] = {
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0
    };
    memcpy(sample.output, identity, sizeof(scalar) * sample.getOutputSize());
    
    // Before training
    std::cout << "Initial state:" << std::endl;
    network.feed(nullptr);
    std::cout << "A = " << std::endl; Printer::print(A);
    std::cout << "B = " << std::endl; Printer::print(B);
    
    network.feed(sample);
    std::cout << "initial error = " << network.getError() << std::endl << std::endl;
    
    // Train
    network.setLearningRate(0.1);
    for(int i = 1;network.getError() > 0.00000001; ++i) {
        network.train(sample);
        if(i % 1000 == 0)
            std::cout << "Round " << i << ": error = " << std::setprecision(10) << network.getError() << std::endl;
    }
    
    // After training
    std::cout << std::endl << "Final state:" << std::endl;
    network.feed();
    std::cout << "A = " << std::endl; Printer::print(A);
    std::cout << "B = " << std::endl; Printer::print(B);
    std::cout << "I = " << std::endl; Printer::print(I);
    
    return 0;
}
