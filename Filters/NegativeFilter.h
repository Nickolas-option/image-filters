#pragma once
#include "BaseFilter.h"

class NegativeFilter : public BaseFilter {
public:
    explicit NegativeFilter(Image& image);
    void Apply() override;
};
