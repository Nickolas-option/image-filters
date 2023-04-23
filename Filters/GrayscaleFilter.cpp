#include "GrayscaleFilter.h"
GrayscaleFilter::GrayscaleFilter(Image& image) : BaseFilter(image) {
}
void GrayscaleFilter::Apply() {
    const double red_coeff = 0.299;
    const double green_coeff = 0.587;
    const double blue_coef = 0.114;
    for (auto& vec : image.GetImageMatrix()) {
        for (auto& pix : vec) {
            pix.Red = static_cast<int32_t>(pix.Red * red_coeff + green_coeff * pix.Green + blue_coef * pix.Blue);
            pix.Blue = pix.Red;
            pix.Green = pix.Red;
        }
    }
}
