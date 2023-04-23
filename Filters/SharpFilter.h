#pragma once
#include "BaseFilter.h"
class SharpFilter : public BaseFilter {
public:
    explicit SharpFilter(Image& image);
    void Apply() override;
};
