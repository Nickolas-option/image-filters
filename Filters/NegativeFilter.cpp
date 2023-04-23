#include "NegativeFilter.h"
NegativeFilter::NegativeFilter(Image& image) : BaseFilter(image) {
}

void NegativeFilter::Apply() {
    const int max_8bit_int = 255;
    for (auto& vec : image.GetImageMatrix()) {
        for (auto& pix : vec) {
            pix.Red = (max_8bit_int - pix.Red);
            pix.Blue = (max_8bit_int - pix.Blue);
            pix.Green = (max_8bit_int - pix.Green);
        }
    }
}
