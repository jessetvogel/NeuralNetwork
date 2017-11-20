#include "trainingset.hpp"
#include "printer.hpp"
#include <iostream>

#define PATH_TRAINING_SET "/Users/jessetvogel/Desktop/data/training.nnts"
#define PATH_TESTING_SET "/Users/jessetvogel/Desktop/data/testing.nnts"

int main(int argc, const char * argv[]) {
    // Load sets
    TrainingSet* trainingSet = TrainingSet::load(PATH_TRAINING_SET);
    TrainingSet* testingSet = TrainingSet::load(PATH_TESTING_SET);

    trainingSet->shuffle();
    testingSet->shuffle();
    
    // Create network
    Network network;
    Builder* b = network.getBuilder();
    
    Volume* input =         b->volume(28, 28, 1);
    FilterSet* filters1 =   b->filterset(5, 5, 1, 8);
    Volume* conv1 =         b->convolution(input, filters1);
    Volume* bias1 =         b->volume(conv1->getDimensions());
    Volume* layer1 =        b->maxpool(b->sigmoid(b->add(conv1, bias1)), 2, 2);
    FilterSet* filters2 =   b->filterset(5, 5, filters1->getDimension(FILTERSET_AMOUNT), 4);
    Volume* conv2 =         b->convolution(layer1, filters2);
    Volume* bias2 =         b->volume(conv2->getDimensions());
    Volume* layer2 =        b->maxpool(b->sigmoid(b->add(conv2, bias2)), 2, 2);
    Matrix* A =             b->matrix(10, layer2->getSize());
    Vector* output =        b->softmax(b->dot(A, layer2));
    
    // Set and initialize parameters
    network.addParameter(filters1);
    network.addParameter(filters2);
    network.addParameter(bias1);
    network.addParameter(bias2);
    network.addParameter(A);
    filters1->initializeValues(0.2);
    filters2->initializeValues(0.2);
    bias1->initializeValues(0.1);
    bias2->initializeValues(0.1);
    A->initializeValues(0.2);
    
    // Set input / output
    network.setInput(input);
    network.setOutput(output);
    
    // Set error function
    network.setErrorType(Network::QUADRATIC);
    
    // Evaluate
    std::cout << "Evaluating testing set ..." << std::endl;
    testingSet->evaluate(network);
    
    // Train
    std::cout << "Training network ..." << std::endl;
    network.setLearningRate(0.1);
    for(int i = 0;i < 1000; ++i) {
        std::cout << "Round #" << (i + 1) << std::endl;
        trainingSet->train(network);
        
        std::cout << "Re-evaluating testing set ..." << std::endl;
        testingSet->evaluate(network);
    }
    
    // Re-evaluate
    std::cout << "Re-evaluating testing set ..." << std::endl;
    testingSet->evaluate(network);
    
    return 0;
}
