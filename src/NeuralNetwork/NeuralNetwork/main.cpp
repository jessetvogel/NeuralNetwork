#include "network.hpp"
#include "printer.hpp"
#include "gradientchecker.hpp"
#include <iostream>

/*

    Maxpool test
 
    - check evaluation of maxpool
    - check backpropagation

 */

int main(int argc, const char * argv[]) {
    Network network;
    Builder* b = network.getBuilder();
    
    // Create volume and filterset
    Volume* input = b->volume(1, 1, 1);
    Volume* output = b->maxpool(input, 1, 1);
    
    // Set values
    scalar x[1] = {
         1.0
    };
    memcpy(input->getValueAddr(), x, sizeof(scalar) * input->getSize());
    
    // Compute output
    network.setOutput(output);
    output->computeValue();
    
    // Print values
    Printer::print("Input = ");
    Printer::print(input);
    Printer::print("Output = ");
    Printer::print(output);

    // Compute some sample to test gradient
    Sample sample(0, output->getSize());
    memcpy(sample.output, output->getValueAddr(), sizeof(scalar) * output->getSize());
    
    // Do something
    network.addParameter(input);
    input->initializeValues(0.1);

//    for(scalar x = 0.0;x <= 1.0001;x += 0.01) {
//        network.setLearningRate(x);
//        input->initializeValues(0.1);
//        
//        network.feed(sample);
//        scalar error = network.getError();
//        network.train(sample);
//        network.feed(sample);
//        
//        std::cout << (network.getError() / error) << std::endl;
//    }
    
    Printer::print("Input = ");
    Printer::print(input);
    Printer::print("Output = ");
    Printer::print(output);

    network.setLearningRate(0.001);
    network.train(sample);
    std::cout << "Error before training: " << network.getError() << std::endl;
    network.feed(sample);
    std::cout << "Error after training: " << network.getError() << std::endl;
    
    Printer::print("dInput = ");
    Printer::printGradient(input);
    Printer::print("Input = ");
    Printer::print(input);
    Printer::print("Output = ");
    Printer::print(output);
    
    return 0;
}
