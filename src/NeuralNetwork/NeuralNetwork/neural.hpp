#ifndef neural_hpp
#define neural_hpp

#include "scalar.hpp"
#include "vector.hpp"
#include "sample.hpp"

#include <vector>

class Neural {

    Variable* input;
    Variable* output;
    
    Variable* trainOutput;
    Scalar* error;
    
    scalar learningRate;
    
    std::vector<Variable*> variables;
    std::vector<Variable*> parameters;
    
public:
    
    Neural() {};
    ~Neural();
    
    inline scalar* getOutput() { return output->getValueAddr(); }
    inline void setLearningRate(scalar alpha) { learningRate = alpha; };
    
    inline void addParameter(Variable* parameter) { parameters.push_back(parameter); };

    void feed(scalar*);
    void train(Sample&);
    
};

#endif
