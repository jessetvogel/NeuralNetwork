#ifndef trainer_hpp
#define trainer_hpp

#include "network.hpp"
#include "sample.hpp"
#include <vector>
#include <string>

class Trainer {
    
    std::vector<Sample*> samples;
    
public:
    
    ~Trainer();
    
    inline size_t amountOfSamples() { return samples.size(); }
    
    bool loadDirectory(std::string);
    bool loadSample(std::string);
    void addSample(Sample*);
    void addSample(Sample&);
    bool store(std::string);

    bool train(Network&);
    
};

#endif
