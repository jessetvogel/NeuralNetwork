#include "convolution.hpp"

Volume* Convolution::create(Volume* volume, FilterSet* filters) {
    // Make sure they are compatible
    if(volume->getDimension(VOLUME_DEPTH) != filters->getDimension(FILTERSET_DEPTH) ||
       volume->getDimension(VOLUME_WIDTH) < filters->getDimension(FILTERSET_WIDTH) ||
       volume->getDimension(VOLUME_HEIGHT) < filters->getDimension(FILTERSET_HEIGHT)) {
        Log::print("Incompatible volume and filter set");
        return nullptr;
    }
    
    // Create object and volume
    dim dimensions[3];
    dimensions[VOLUME_WIDTH] = volume->getDimension(VOLUME_WIDTH) - filters->getDimension(FILTERSET_WIDTH) + 1;
    dimensions[VOLUME_HEIGHT] = volume->getDimension(VOLUME_HEIGHT) - filters->getDimension(FILTERSET_HEIGHT) + 1;
    dimensions[VOLUME_DEPTH] = filters->getDimension(FILTERSET_AMOUNT);
    
    return new Volume(new Convolution(volume, filters), dimensions);
}

void Convolution::setResult(Variable* variable) {
    result = variable;
    result->addChild(volume);
    result->addChild(filters);
}

void Convolution::evaluate() {
    // Compute convolution
    scalar* valueResult;
    scalar* valueVolume;
    scalar* valueFilters;

    dim FW = filters->getDimension(FILTERSET_WIDTH);
    dim FH = filters->getDimension(FILTERSET_HEIGHT);
    dim FD = filters->getDimension(FILTERSET_DEPTH);
    dim FA = filters->getDimension(FILTERSET_AMOUNT);

    dim VW = volume->getDimension(VOLUME_WIDTH);
    dim VH = volume->getDimension(VOLUME_HEIGHT);
    
    dim RW = VW - FW + 1;
    dim RH = VH - FH + 1;

    // First set valueResult to 0.0
    dim RS = result->getSize();
    valueResult = result->getValueAddr();
    for(dim i = 0;i < RS; ++i) *(valueResult++) = 0.0;
    
    // Surely there is some logic to this (Hint: make a drawing with a lot of arrows)
    valueResult = result->getValueAddr();
    scalar* volumeStartingPosition = volume->getValueAddr();
    for(dim w = 0;w < RW; ++w) {
        for(dim h = 0;h < RH; ++h) {
            valueVolume = volumeStartingPosition;
            valueFilters = filters->getValueAddr();
            for(dim fw = 0;fw < FW; ++fw) {
                for(dim fh = 0;fh < FH; ++fh) {
                    for(dim fd = 0;fd < FD; ++fd) {
                        for(dim fa = 0;fa < FA; ++fa)
                            *(valueResult++) += (*valueVolume) * (*(valueFilters++));
                        valueResult -= FA; // Return back
                        ++ valueVolume;
                    }
                }
                valueVolume += (VH - FH) * FD; // Next column
            }
            valueResult += FA; // Go to next coordinate
            volumeStartingPosition += FD; // One step down (equal to VD)
        }
        volumeStartingPosition += (FH - 1) * FD; // Back to the top, and next column
    }
}

void Convolution::backpropagate() {
    // Compute contribution to gradients
    scalar* valueVolume;
    scalar* valueFilters;
    scalar* gradientResult;
    scalar* gradientVolume;
    scalar* gradientFilters;
    
    dim FW = filters->getDimension(FILTERSET_WIDTH);
    dim FH = filters->getDimension(FILTERSET_HEIGHT);
    dim FD = filters->getDimension(FILTERSET_DEPTH);
    dim FA = filters->getDimension(FILTERSET_AMOUNT);
    
    dim VW = volume->getDimension(VOLUME_WIDTH);
    dim VH = volume->getDimension(VOLUME_HEIGHT);
    
    dim RW = VW - FW + 1;
    dim RH = VH - FH + 1;
    
    // The logic here is to follow the exact same path as in evaluate(), so that we have little to adjust
    gradientResult = result->getGradientAddr();
    scalar* volumeValueStartingPosition = volume->getValueAddr();
    scalar* volumeGradientStartingPosition = volume->getGradientAddr();
    for(dim w = 0;w < RW; ++w) {
        for(dim h = 0;h < RH; ++h) {
            valueVolume = volumeValueStartingPosition; gradientVolume = volumeGradientStartingPosition;
            valueFilters = filters->getValueAddr(); gradientFilters = filters->getGradientAddr();
            for(dim fw = 0;fw < FW; ++fw) {
                for(dim fh = 0;fh < FH; ++fh) {
                    for(dim fd = 0;fd < FD; ++fd) {
                        for(dim fa = 0;fa < FA; ++fa) {
                            *gradientVolume += (*gradientResult) * (*(valueFilters++));
                            *(gradientFilters++) += (*gradientResult) * (*valueVolume);
                            ++gradientResult;
                        }
                        gradientResult -= FA; // Return back
                        ++ valueVolume; ++ gradientVolume;
                    }
                }
                valueVolume += (VH - FH) * FD; gradientVolume += (VH - FH) * FD; // Next column
            }
            gradientResult += FA; // Go to next coordinate
            volumeValueStartingPosition += FD; volumeGradientStartingPosition += FD; // One step down (equal to VD)
        }
        volumeValueStartingPosition += (FH - 1) * FD; volumeGradientStartingPosition += (FH - 1) * FD; // Back to the top, and next column
    }
}
