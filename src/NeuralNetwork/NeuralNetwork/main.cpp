#include "trainingset.hpp"
#include "printer.hpp"

int main(int argc, const char * argv[]) {

    // Load set
    TrainingSet* set = TrainingSet::load("/Users/jessetvogel/Desktop/data/training.nnts");
    Printer::print(set);
    
    return 0;
}
