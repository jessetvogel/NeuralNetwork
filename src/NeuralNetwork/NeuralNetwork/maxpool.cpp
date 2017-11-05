#include "maxpool.hpp"

Volume* MaxPool::create(Volume* a, int w, int h) {
    // Make sure they are compatible
    if(a->getDimension(VOLUME_WIDTH) % w != 0 ||
       a->getDimension(VOLUME_HEIGHT) % h != 0) {
        Log::print("Incompatible volume and width/height");
        return nullptr;
    }
    
    // Create
    dim dimensions[3];
    dimensions[VOLUME_WIDTH] = a->getDimension(VOLUME_WIDTH) / w;
    dimensions[VOLUME_HEIGHT] = a->getDimension(VOLUME_HEIGHT) / h;
    dimensions[VOLUME_DEPTH] = a->getDimension(VOLUME_DEPTH);
    return new Volume(new MaxPool(a, w, h), dimensions);
}

void MaxPool::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
}

void MaxPool::evaluate() {
    // Compute maxpool
    // TODO
}

void MaxPool::backpropagate() {
    // Compute contribution to gradients
    // TODO
}
