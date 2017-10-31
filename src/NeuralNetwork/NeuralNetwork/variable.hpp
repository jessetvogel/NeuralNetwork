#ifndef variable_hpp
#define variable_hpp

#include <vector>
#include <random>
#include "math.hpp"

class Variable {
    
    const dimension size;
    
    bool computedValue;
    bool computedGradient;
    
    Function* function;
    
    std::vector<Variable*> inputs;
    std::vector<Variable*> dependents;
    
    inline void addInput(Variable* input) { inputs.push_back(input); }
    inline void addDependent(Variable* dependent) { dependents.push_back(dependent); }
    
    static std::default_random_engine randomGenerator;
    
protected:
    
    scalar* value;
    scalar* gradient;
    
    Variable(dimension, Function*);

public:
    
    ~Variable();
    
    inline dimension getSize() { return size; }
    inline scalar* getValueAddr() { return value; }
    inline scalar* getGradientAddr() { return gradient; }
    
    inline void addChild(Variable* child) { addInput(child); child->addDependent(this); }
    
    void initializeValues(scalar);
    
    void computeValue();
    void computeGradient();
    
    void resetValue();
    void resetGradient();
    
};

#endif
