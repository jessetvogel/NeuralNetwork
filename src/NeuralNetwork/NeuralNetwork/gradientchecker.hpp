#ifndef gradientchecker_hpp
#define gradientchecker_hpp

#include "network.hpp"

class GradientChecker {

public:
    
    static void check(Network&, scalar*, scalar*);
    
};

#endif
