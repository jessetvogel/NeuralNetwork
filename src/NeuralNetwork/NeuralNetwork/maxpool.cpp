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
    scalar* valueResult;
    scalar* valueA;

    dim W = a->getDimension(VOLUME_WIDTH);
    dim H = a->getDimension(VOLUME_HEIGHT);
    dim D = a->getDimension(VOLUME_DEPTH);

    dim __w = W / width;
    dim __h = H / height;
    
    // Preset values (TODO: in hoeverre is dit nodig? kan dit optimaler?)
    valueResult = result->getValueAddr();
    valueA = a->getValueAddr();
    for(dim w = 0;w < __w; ++w) {
        for(dim h = 0;h < __h; ++h) {
            for(dim d = 0;d < D; ++d)
                *(valueResult++) = *(valueA++);
            valueA += D * (__h - 1);
        }
        valueA += D * H * (__w - 1);
    }
    
    // Find maxima
    valueResult = result->getValueAddr();
    valueA = a->getValueAddr();
    for(dim w = 0;w < W; ++w) {
        for(dim h = 0;h < H; ++h) {
            for(dim d = 0;d < D; ++d) {
                if(*valueA > *valueResult)
                    *valueResult = *valueA;
                ++valueA;
                ++valueResult;
            }
            if((h + 1) % height != 0)
                valueResult -= D; // Go to first layer
        }
        if((w + 1) % width != 0)
            valueResult -= D * __h; // Go to top
    }
}

void MaxPool::backpropagate() {
    // Compute contribution to gradients
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    scalar* gradientResult = result->getGradientAddr();
    scalar* gradientA = a->getGradientAddr();
    
    dim W = a->getDimension(VOLUME_WIDTH);
    dim H = a->getDimension(VOLUME_HEIGHT);
    dim D = a->getDimension(VOLUME_DEPTH);
    
    dim __h = H / height;
    
    // Copy gradient for maxima, others are all zero
    for(dim w = 0;w < W; ++w) {
        for(dim h = 0;h < H; ++h) {
            for(dim d = 0;d < D; ++d) {
                if(*(valueA++) == *(valueResult++))
                    *gradientA += *gradientResult;
                ++gradientA;
                ++gradientResult;
            }
            if((h + 1) % height != 0) {
                valueResult -= D; // Go to first layer
                gradientResult -= D;
            }
        }
        if((w + 1) % width != 0) {
            valueResult -= D * __h; // Go to top
            gradientResult -= D * __h;
        }
    }
}
