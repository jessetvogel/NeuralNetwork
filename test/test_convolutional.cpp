#include "network.hpp"
#include "printer.hpp"
#include "gradientchecker.hpp"
#include <iostream>

/*
 
 Checks steps in convolutional layer:
 - feed forward
 - check gradient
 - optimize filterset (train network)
 
 Input =
 [ 1, 5, 9, 13 ] [ 17, 21, 25, 29 ]
 [ 2, 6, 10, 14 ] [ 18, 22, 26, 30 ]
 [ 3, 7, 11, 15 ] [ 19, 23, 27, 31 ]
 [ 4, 8, 12, 16 ] [ 20, 24, 28, 32 ]
 
 Filterset =
 [ 0, 0 ] [ 1, 0 ]
 [ 0, 0 ] [ 0, 0 ]
 
 [ 0, 0 ] [ 0, 0 ]
 [ 0, 1 ] [ 0, 0 ]
 
 Output =
 [ 17, 21, 25 ] [ 6, 10, 14 ]
 [ 18, 22, 26 ] [ 7, 11, 15 ]
 [ 19, 23, 27 ] [ 8, 12, 16 ]
 
 */

int main(int argc, const char * argv[]) {
    Network network;
    Builder* b = network.getBuilder();
    
    // Create volume and filterset
    Volume* input = b->volume(4, 4, 2);
    FilterSet* filterset = b->filterset(2, 2, 2, 2);
    Volume* output = b->convolution(input, filterset);
    
    // Set values
    scalar x[32] = {
        1.0, 17.0,  2.0, 18.0,
        3.0, 19.0,  4.0, 20.0,
        5.0, 21.0,  6.0, 22.0,
        7.0, 23.0,  8.0, 24.0,
        
        9.0, 25.0, 10.0, 26.0,
        11.0, 27.0, 12.0, 28.0,
        13.0, 29.0, 14.0, 30.0,
        15.0, 31.0, 16.0, 32.0
    };
    memcpy(input->getValueAddr(), x, sizeof(scalar) * 32);
    
    scalar f[16] = {
        0.0, 0.0,
        1.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        
        0.0, 0.0,
        0.0, 0.0,
        0.0, 1.0,
        0.0, 0.0,
    };
    memcpy(filterset->getValueAddr(), f, sizeof(scalar) * 16);
    
    // Compute output
    network.setOutput(output);
    output->computeValue();
    
    // Print values
    Printer::print("Input = ");
    Printer::print(input);
    Printer::print("Filterset = ");
    Printer::print(filterset);
    Printer::print("Output = ");
    Printer::print(output);
    
    // Compute some sample to test gradient
    Sample sample(0, 18);
    memcpy(sample.output, output->getValueAddr(), sizeof(scalar) * 18);
    
    // Add filterset as a parameter and randomise its value
    filterset->initializeValues(0.1);
    network.addParameter(filterset);
    
    // Print values
    network.feed(sample);
    Printer::print("Input = ");
    Printer::print(input);
    Printer::print("Filterset = ");
    Printer::print(filterset);
    Printer::print("Output = ");
    Printer::print(output);
    
    // Check gradients
    GradientChecker::check(network, sample);
    
    // Train
    for(int i = 1;network.getError() > 0.0001; ++i) {
        network.train(sample);
        std::cout << "Round #" << i << " - error: " << network.getError() << std::endl;
    }
    std::cout << std::endl;
    
    // Print result
    Printer::print("Optimized filterset = ");
    Printer::print(filterset);
    
    Printer::print("Output = ");
    Printer::print(output);
    
    return 0;
}
