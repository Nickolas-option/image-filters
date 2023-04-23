#pragma once
#include "BaseFilter.h"
class EdgeFilter : public BaseFilter {
public:
    explicit EdgeFilter(Image& image);
    void Apply(double threshold) override;
};
