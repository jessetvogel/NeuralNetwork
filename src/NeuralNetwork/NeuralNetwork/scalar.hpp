#ifndef scalar_hpp
#define scalar_hpp

#include "variable.hpp"

class Scalar : public Variable {
    
public:
    
    Scalar(Function*);
    
    void findGradients(); // Such a function (maybe another name) can only be called on scalars. This will cause a chain reaction (pun intended) of computing gradients (reverse mode differentiation).
    
};

#endif
