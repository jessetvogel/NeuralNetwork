#ifndef variable_hpp
#define variable_hpp

#include <vector>
#include <random>
#include "math.hpp"

class Variable {
    
    Function* function;
    
    bool computedValue;
    bool computedGradient;
    
    std::vector<Variable*> inputs;
    std::vector<Variable*> dependents;
    
    inline void addInput(Variable* input) { inputs.push_back(input); }
    inline void addDependent(Variable* dependent) { dependents.push_back(dependent); }
    
    static std::default_random_engine randomGenerator;
    
protected:
    
    Variable(Function*);
    
    dimension size;
    dimension order;
    dimension* dim;
    
    scalar* value;
    scalar* gradient;
    
public:
    
    ~Variable();
    
    inline dimension getSize() { return size; }
    inline dimension getOrder() { return order; }
    inline dimension getDimension(int n) { return dim[n]; }
    
    inline scalar* getValueAddr() { return value; }
    inline scalar* getGradientAddr() { return gradient; }
    
    inline void addChild(Variable* child) { addInput(child); child->addDependent(this); }

    void computeValue();
    void computeGradient();
    
    void resetValue();
    void resetGradient();

    void initializeValues(scalar);
    
};

#endif
