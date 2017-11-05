#ifndef network_hpp
#define network_hpp

#include "tensor.hpp"
#include "sample.hpp"

#include <vector>

class Builder;

class Network {
    
public:

    enum ErrorType { QUADRATIC, CROSS_ENTROPY };
    
private:
    
    Builder* builder;
    
    Variable* input;
    Variable* output;
    
    Variable* trainOutput;
    
    scalar learningRate;
    ErrorType errorType;
    
    std::vector<Variable*> variables;
    std::vector<Variable*> parameters;
    
    void deleteVariable(Variable*);
    void updateError();
    
public:
    
    Network();
    ~Network();
    
    inline Builder* getBuilder() { return builder; }
    
    void setInput(Variable*);
    void setOutput(Variable*);
    
    inline void addParameter(Variable* parameter) { parameters.push_back(parameter); }

    inline void setLearningRate(scalar alpha) { learningRate = alpha; };
    inline void setErrorType(ErrorType e) { if(errorType != e) { errorType = e; updateError(); } }

    bool feed(scalar*);
    bool feed(Sample&);
    inline bool feed() { return feed(nullptr); }
    
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
