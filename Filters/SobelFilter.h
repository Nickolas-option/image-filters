#include "BaseFilter.h"
#pragma once

class SobelFilter : public BaseFilter {
public:
    explicit SobelFilter(Image& image);
    void Apply() override;
};
