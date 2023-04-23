#pragma once
#include "BaseFilter.h"
class CropFilter : public BaseFilter {
public:
    explicit CropFilter(Image& image);
    void Apply(size_t new_width, size_t new_height) override;
};
