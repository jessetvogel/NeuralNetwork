#include <iostream>

#include "network.hpp"
#include "printer.hpp"

/*
 
 Similate XOR gate
 
   | 0 | 1 |
   +---+---+
 0 | 0   1
 1 | 1   0
 
 Network design:
 
           A             B
 input(2) --> vector(2) --> scalar(1)
 
 */

int main(int argc, const char * argv[]) {
    // Setup network
    Network network(1);
    Builder* b = network.getBuilder();
    
    Vector* input = b->vector(2);
    
    Vector* bias1 = b->vector(2);
    Vector* bias2 = b->vector(1);
    
    Matrix* A = b->matrix(2, 2);
    Matrix* B = b->matrix(1, 2);
    
    Vector* output = b->sigmoid(b->add(bias2, b->dot(B, b->sigmoid(b->add(bias1, b->dot(A, input))))));
    
    network.setInput(input);
    network.setOutput(output);

    network.addParameter(A);
    network.addParameter(B);
    network.addParameter(bias1);
    network.addParameter(bias2);

    A->initializeValues(0.1);
    B->initializeValues(0.1);
    bias1->initializeValues(0.1);
    bias2->initializeValues(0.1);
    
    // Create samples
    Sample case_1(2, 1);
    *case_1.input = 0.0;
    *(case_1.input + 1) = 0.0;
    *case_1.output = 0.0;
    
    Sample case_2(2, 1);
    *case_2.input = 0.0;
    *(case_2.input + 1) = 1.0;
    *case_2.output = 1.0;
    
    Sample case_3(2, 1);
    *case_3.input = 1.0;
    *(case_3.input + 1) = 0.0;
    *case_3.output = 1.0;
    
    Sample case_4(2, 1);
    *case_4.input = 1.0;
    *(case_4.input + 1) = 1.0;
    *case_4.output = 0.0;

    // Show errors on initial state
    std::cout << "Initial state:" << std::endl;
    network.feed(case_1);
    std::cout << "error 1 = " << network.getError() << std::endl;
    network.feed(case_2);
    std::cout << "error 2 = " << network.getError() << std::endl;
    network.feed(case_3);
    std::cout << "error 3 = " << network.getError() << std::endl;
    network.feed(case_4);
    std::cout << "error 4 = " << network.getError() << std::endl << std::endl;
    
    // Train
    int N = 500;
    network.setLearningRate(0.1);
    for(int i = 0;i < N; ++i) {
        network.train(case_1);
        network.train(case_2);
        network.train(case_3);
        network.train(case_4);
    }
    
    // Show errors on final state
    std::cout << "Final state:" << std::endl;
    network.feed(case_1);
    std::cout << "error 1 = " << network.getError() << std::endl;
    network.feed(case_2);
    std::cout << "error 2 = " << network.getError() << std::endl;
    network.feed(case_3);
    std::cout << "error 3 = " << network.getError() << std::endl;
    network.feed(case_4);
    std::cout << "error 4 = " << network.getError() << std::endl << std::endl;

    return 0;
}
