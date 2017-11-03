#include "trainer.hpp"
#include <dirent.h>

Trainer::~Trainer() {
    // Delete samples
    for(auto it = samples.begin();it != samples.end(); ++it)
        delete *it;
}

bool Trainer::loadDirectory(std::string path) {
    // Try to open directory
    DIR *directory;
    if((directory = opendir(path.c_str())) == NULL)
        return false;
    
    // Scan files
    struct dirent *entry;
    while((entry = readdir(directory)) != NULL) {
        // Check extension
        std::string filename = std::string(entry->d_name);
        if(filename.length() < 5) continue;
        if(filename.compare(filename.length() - 5, 5, ".nnts") != 0) continue;
        
        // Load sample
        loadSample(path + "/" + filename);
    }
    
    closedir(directory);
    return true;
}

bool Trainer::loadSample(std::string path) {
    // Try to load sample from path
    Sample* sample = Sample::load(path);
    if(sample == nullptr) return false;
    
    // Add to list of samples
    samples.push_back(sample);
    return true;
}

void Trainer::addSample(Sample* sample) {
    samples.push_back(sample);
}

void Trainer::addSample(Sample& sample) {
    addSample(sample.duplicate());
}

bool Trainer::store(std::string path) {
    // Store samples
    unsigned int id = 0;
    for(auto it = samples.begin();it != samples.end(); ++it) {
        if(!((*it)->save(path + "/sample_" + std::to_string(id++) + ".nnts")))
            return false;
    }
    return true;
}

bool Trainer::train(Network& network) {
    for(auto it = samples.begin();it != samples.end(); ++it) {
        if(!network.train(**it))
            return false;
    }
    return true;
}
