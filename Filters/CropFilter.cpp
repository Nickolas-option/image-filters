#include "CropFilter.h"

#include "algorithm"
#include "BaseFilter.h"

CropFilter::CropFilter(Image& image) : BaseFilter(image) {
}
void CropFilter::Apply(size_t new_width, size_t new_height) {
    auto new_image_matrix = image.GetImageMatrix();
    std::reverse(new_image_matrix.begin(), new_image_matrix.end());

    std::vector<std::vector<Pixel>> new_data;
    new_data.reserve(new_image_matrix.size());
    for (size_t i = 0; i < new_height; ++i) {
        std::vector<Pixel> new_row;
        new_row.reserve(new_image_matrix[0].size());
        for (size_t j = 0; j < new_width; ++j) {
            Pixel pix = new_image_matrix[i][j];
            new_row.push_back(pix);
        }
        new_data.push_back(new_row);
    }
    std::reverse(new_data.begin(), new_data.end());
    image.GetImageMatrix() = std::move(new_data);
}
