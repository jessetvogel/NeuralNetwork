#ifndef variable_hpp
#define variable_hpp

#include <vector>
#include <random>
#include "math.hpp"

class Variable {
    
    Function* function;
    
    std::vector<Variable*> inputs;
    std::vector<Variable*> dependents;
    
    bool computedValue;
    bool computedGradient;
    
    inline void addInput(Variable* input) { inputs.push_back(input); }
    inline void addDependent(Variable* dependent) { dependents.push_back(dependent); }
    
    // TODO: This shouldn't be here?
    static std::default_random_engine randomGenerator;
    
protected:
    
    Variable(Function*);
    
    dim size;
    scalar* value;
    scalar* gradient;
    
public:
    
    ~Variable();
    
    inline dim getSize() { return size; }
    inline scalar* getValueAddr() { return value; }
    inline scalar* getGradientAddr() { return gradient; }
    
    inline void addChild(Variable* child) { addInput(child); child->addDependent(this); }

    inline void resetValue() { computedValue = false; }
    inline void resetGradient() { computedGradient = false; }
    
    void computeValue();
    void computeGradient();

    void initializeValues(scalar);
    
};

#endif
