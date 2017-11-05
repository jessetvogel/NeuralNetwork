#include <iostream>

#include "network.hpp"
#include "printer.hpp"
#include "gradientchecker.hpp"

int main(int argc, const char * argv[]) {
    
    Network network;
    Builder* b = network.getBuilder();
    
    Vector* i = b->vector(3);
    Vector* o = b->softmax(i);
    
    network.setOutput(o);
    network.addParameter(i);
    
    i->initializeValues(0.1);
    
    network.feed();
    
    Printer::print(i);
    Printer::print(o);
    
    Sample sample(0, 3);
    scalar y[3] = { 0.1, 0.7, 0.2 };
    memcpy(sample.output, y, sizeof(scalar) * 3);
    
    GradientChecker::check(network, sample);
    
    network.setLearningRate(0.01);
    for(int i = 1;network.getError() > 0.000001; ++i) {
        network.train(sample);
        std::cout << "Round #" << i << " - error = " << network.getError() << std::endl;
    }
    
    Printer::print(i);
    Printer::print(o);
    
    return 0;
}
