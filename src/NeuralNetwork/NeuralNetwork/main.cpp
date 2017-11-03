#include <iostream>
#include <iomanip>

#include "network.hpp"
#include "printer.hpp"
#include "trainer.hpp"

int main(int argc, const char * argv[]) {

    Network network;
    network.setOutput(network.getBuilder()->vector(3));
    
    Trainer trainer;
    trainer.loadDirectory("/Users/jessetvogel/Desktop/samples");
    trainer.train(network);

    return 0;
}
