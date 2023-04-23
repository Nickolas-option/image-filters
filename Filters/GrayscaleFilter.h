#pragma once
#include "BaseFilter.h"

class GrayscaleFilter : public BaseFilter {
public:
    explicit GrayscaleFilter(Image& image);
    void Apply() override;
};
