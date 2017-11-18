#include "network.hpp"
#include "printer.hpp"
#include "gradientchecker.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {
    
    Sample* sample = Sample::load("/Users/jessetvogel/Desktop/test123.nnts");
    Printer::print(*sample);
    
    return 0;
}
