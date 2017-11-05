#include <iostream>

#include "network.hpp"

int main(int argc, const char * argv[]) {

    std::cout << "sizeof scalar = " << sizeof(Scalar) << std::endl;
    std::cout << "sizeof vector = " << sizeof(Vector) << std::endl;
    std::cout << "sizeof matrix = " << sizeof(Matrix) << std::endl;
    
    return 0;
}
