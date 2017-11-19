#include "trainingset.hpp"
#include "printer.hpp"

/*
 
 Create, store and load a training set (for a XOR gate)
 
 */

#define PATH "/Users/jessetvogel/Desktop/test_xor.nnts"

int main(int argc, const char * argv[]) {
    // Create set
    TrainingSet set(1, 1, 0.0, 1.0, 0.0, 1.0, 2, 1);
    
    scalar input[2];
    scalar output[1];
    
    // 0 ^ 0 = 0
    input[0] = 0.0; input[1] = 0.0; output[0] = 0.0; set.addSample(input, output);
    
    // 0 ^ 1 = 1
    input[0] = 0.0; input[1] = 1.0; output[0] = 1.0; set.addSample(input, output);
    
    // 1 ^ 0 = 1
    input[0] = 1.0; input[1] = 0.0; output[0] = 1.0; set.addSample(input, output);
    
    // 1 ^ 1 = 0
    input[0] = 1.0; input[1] = 1.0; output[0] = 0.0; set.addSample(input, output);
    
    // Save set
    set.store(PATH);
    
    // Load and print set
    TrainingSet* newSet = TrainingSet::load(PATH);
    Printer::print(newSet);
    
    return 0;
}
