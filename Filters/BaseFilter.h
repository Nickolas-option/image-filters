#pragma once

#include <cstdlib>
#include <vector>

#include "../image.h"
class BaseFilter {
public:
    explicit BaseFilter(Image& image);

    virtual void Apply() {
    }
    virtual void Apply(double param) {
    }
    virtual void Apply(std::size_t param1, std::size_t param2) {
    }

protected:
    Image& image;
};