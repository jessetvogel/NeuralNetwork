#ifndef variable_hpp
#define variable_hpp

#include <vector>
#include "math.hpp"

class Variable {
    
    const unsigned int n;
    
    bool computedValue;
    bool computedGradient;
    
    Function* function;
    
    std::vector<Variable*> inputs;
    std::vector<Variable*> dependents;
    
    inline void addInput(Variable* input) { inputs.push_back(input); }
    inline void addDependent(Variable* dependent) { dependents.push_back(dependent); }
    
protected:
    
    scalar* value;
    scalar* gradient;
    
    Variable(unsigned int, Function*);
    ~Variable();

public:
    
    inline unsigned int getSize() { return n; }
    inline Function* getFunction() { return function; }
    inline scalar* getValueAddr() { return value; }
    inline scalar* getGradientAddr() { return gradient; }
    
    inline void addChild(Variable* child) { addInput(child); child->addDependent(this); }
    
    void computeValue();
    void computeGradient();
    
};

#endif
