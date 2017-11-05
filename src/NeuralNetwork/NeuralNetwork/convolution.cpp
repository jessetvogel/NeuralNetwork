#include "convolution.hpp"

Volume* Convolution::create(Volume* a, FilterSet* b) {
    // Make sure they are compatible
    if(a->getDimension(VOLUME_DEPTH) != b->getDimension(FILTERSET_DEPTH) ||
       a->getDimension(VOLUME_WIDTH) < b->getDimension(FILTERSET_WIDTH) ||
       a->getDimension(VOLUME_HEIGHT) < b->getDimension(FILTERSET_HEIGHT)) {
        Log::print("Incompatible volume and filter set");
        return nullptr;
    }
    
    // Create object and volume
    dim dimensions[3];
    dimensions[VOLUME_WIDTH] = a->getDimension(VOLUME_WIDTH) - b->getDimension(FILTERSET_WIDTH) + 1;
    dimensions[VOLUME_HEIGHT] = a->getDimension(VOLUME_HEIGHT) - b->getDimension(FILTERSET_HEIGHT) + 1;
    dimensions[VOLUME_DEPTH] = b->getDimension(FILTERSET_AMOUNT);
    return new Volume(new Convolution(a, b), dimensions);
}

void Convolution::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
    result->addChild(b);
}

void Convolution::evaluate() {
    // Compute convolution
    scalar* valueResult = result->getValueAddr();
    
    dim W = a->getDimension(VOLUME_WIDTH) - b->getDimension(FILTERSET_WIDTH) + 1;
    dim H = a->getDimension(VOLUME_HEIGHT) - b->getDimension(FILTERSET_HEIGHT) + 1;
    dim D = b->getDimension(FILTERSET_AMOUNT);
    
    for(dim w = 0;w < W; ++w) {
        for(dim h = 0;h < H; ++h) {
            for(dim d = 0;d < D; ++d) {
                // TODO
            }
        }
    }
}

void Convolution::backpropagate() {
    // Compute contribution to gradients
    // TODO
}
