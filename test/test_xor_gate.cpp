#include <iostream>

#include "network.hpp"
#include "printer.hpp"

#include "gradientchecker.hpp"

/*
 
 Simulate XOR gate
 
 | 0 | 1 |
 +---+---+
 0 | 0   1
 1 | 1   0
 
 Network design:
 
 A, add bias, sigmoid             B, add bias, sigmoid
 input(2) ----------------------> vector(2) ---------------------> scalar(1)
 
 */

int main(int argc, const char * argv[]) {
    // Setup network
    Network network;
    Builder* b = network.getBuilder();
    
    auto input = b->vector<2>();
    
    auto bias1 = b->vector<2>();
    auto bias2 = b->vector<1>();
    
    auto A = b->matrix<2, 2>();
    auto B = b->matrix<1, 2>();
    
    auto output = b->sigmoid(b->add(bias2, b->dot(B, b->sigmoid(b->add(bias1, b->dot(A, input))))));
    
    network.setInput(input);
    network.setOutput(output);
    
    network.addParameter(A);
    network.addParameter(B);
    network.addParameter(bias1);
    network.addParameter(bias2);
    
    // Possible 'solution', found on the internet
    //    scalar* valueA = A->getValueAddr(); *valueA = 20.0; *(valueA+1) = 20.0; *(valueA+2) = -20.0; *(valueA+3) = -20.0;
    //    scalar* valueB = B->getValueAddr(); *valueB = 20.0; *(valueB+1) = 20.0;
    //    scalar* valueBias1 = bias1->getValueAddr(); *valueBias1 = -10.0; *(valueBias1+1) = 30.0;
    //    scalar* valueBias2 = bias2->getValueAddr(); *valueBias2 = -30.0;
    
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
    
    // Check gradients for all 4 cases
    GradientChecker::check(network, case_1);
    GradientChecker::check(network, case_2);
    GradientChecker::check(network, case_3);
    GradientChecker::check(network, case_4);
    
    // Show errors on initial state
    std::cout << "Initial state:" << std::endl;
    
    std::cout << "A = " << std::endl; Printer::print(A);
    std::cout << "B = " << std::endl; Printer::print(B);
    std::cout << "bias_1 = " << std::endl; Printer::print(bias1);
    std::cout << "bias_2 = " << std::endl; Printer::print(bias2);
    
    network.feed(case_1);
    std::cout << "error 1 = " << network.getError() << std::endl;
    network.feed(case_2);
    std::cout << "error 2 = " << network.getError() << std::endl;
    network.feed(case_3);
    std::cout << "error 3 = " << network.getError() << std::endl;
    network.feed(case_4);
    std::cout << "error 4 = " << network.getError() << std::endl << std::endl;
    
    // Train network until average error of 0.0001 is reached
    int i = 0;
    network.setLearningRate(0.05);
    scalar totalError = 1.0;
    while(totalError / 4.0 > 0.0001) {
        i ++;
        totalError = 0.0;
        network.train(case_1); totalError += network.getError();
        network.train(case_2); totalError += network.getError();
        network.train(case_3); totalError += network.getError();
        network.train(case_4); totalError += network.getError();
        if(i % 1000 == 0)
            std::cout << "Round #" << i << " - mean error = " << (totalError / 4.0) << std::endl;
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
    
    // Show final parameters
    std::cout << "A = " << std::endl; Printer::print(A);
    std::cout << "B = " << std::endl; Printer::print(B);
    std::cout << "bias_1 = " << std::endl; Printer::print(bias1);
    std::cout << "bias_2 = " << std::endl; Printer::print(bias2);
    
    return 0;
}
