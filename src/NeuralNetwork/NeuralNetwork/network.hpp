#ifndef network_hpp
#define network_hpp

#include "scalar.hpp"
#include "sample.hpp"

#include <vector>

class Builder;

class Network {
    
    Builder* builder;
    
    Variable* input;
    Variable* output;
    
    Variable* trainOutput;
    
    scalar learningRate;
    
    std::vector<Variable*> variables;
    std::vector<Variable*> parameters;
    
public:
    
    Network(dimension);
    ~Network();
    
    inline Builder* getBuilder() { return builder; }
    
    void setInput(Variable*);
    void setOutput(Variable*);
    inline void addParameter(Variable* parameter) { parameters.push_back(parameter); };

    inline void setLearningRate(scalar alpha) { learningRate = alpha; };

    bool feed(scalar*);
    bool feed(Sample&);
    bool train(Sample&);
    inline scalar getError() { if(error == nullptr) return -1.0; error->computeValue(); return *(error->getValueAddr()); }
    
    inline void addVariable(Variable* variable) { variables.push_back(variable); }; // TODO: preferably this is invisible for everyone except the Builder class
  
    
    // Maybe remove this at some point (TODO)
    inline std::vector<Variable*>* getParameters() { return &parameters; };
    inline std::vector<Variable*>* getVariables() { return &variables; };
    
    Scalar* error; // TODO: move to private
};

#include "builder.hpp"

#endif
