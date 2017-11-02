#include <iostream>

#include "network.hpp"
#include "printer.hpp"

int main(int argc, const char * argv[]) {
    
    Network network;
    Builder* b = network.getBuilder();
    
    Vector* i = b->vector(3);
    Vector* o = b->softmax(i);
    
    network.setOutput(o);
    
    scalar x[3] = { 800.0, 800.0, 800.0 };
    memcpy(i->getValueAddr(), x, sizeof(scalar) * i->getSize());
    
    network.feed();
    
    Printer::printVector(i);
    Printer::printVector(o);
    
    return 0;
}
