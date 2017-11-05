#include <iostream>

#include "network.hpp"

int main(int argc, const char * argv[]) {

//    std::cout << "sizeof scalar = " << sizeof(Scalar) << std::endl;
//    std::cout << "sizeof vector = " << sizeof(Vector) << std::endl;
//    std::cout << "sizeof matrix = " << sizeof(Matrix) << std::endl;
//    std::cout << "sizeof volume = " << sizeof(Volume) << std::endl;
//    std::cout << "sizeof filterset = " << sizeof(FilterSet) << std::endl;
//    std::cout << "sizeof network = " << sizeof(Network) << std::endl;
    
    Network network;
    Builder* b = network.getBuilder();
    
    Volume* volume = b->volume(16, 16, 3);
    FilterSet* filterset = b->filterset(5, 5, 3, 10);
    
    Volume* output = b->convolution(volume, filterset);
    
    
    network.setInput(volume);
    network.setOutput(output);
    
    return 0;
}
