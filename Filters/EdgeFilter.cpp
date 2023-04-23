#include "EdgeFilter.h"

#include "GaussianBlur.h"
EdgeFilter::EdgeFilter(Image& image) : BaseFilter(image) {
}
void EdgeFilter::Apply(double threshold) {
    const std::vector<double> matrix_coeffs = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    auto m = GaussianBlur::Matrix{(image), matrix_coeffs};

    const int max_8_bit_int = 255;
    std::vector<std::vector<Pixel>> new_matrix;
    auto& image_matrix = image.GetImageMatrix();
    new_matrix.resize(image_matrix.size(), std::vector<Pixel>(image_matrix[0].size(), Pixel{0, 0, 0}));

    for (int32_t i = 0; i < image_matrix.size(); i++) {
        for (int32_t j = 0; j < image_matrix[i].size(); j++) {

            auto [red, green, blue] = m.ApplyMatrix(i, j);

            new_matrix[i][j].Red =
                static_cast<int32_t>(max_8_bit_int * std::min(1.0, std::max(0.0, red / max_8_bit_int)));
            new_matrix[i][j].Green =
                static_cast<int32_t>(max_8_bit_int * std::min(1.0, std::max(0.0, green / max_8_bit_int)));
            new_matrix[i][j].Blue =
                static_cast<int32_t>(max_8_bit_int * std::min(1.0, std::max(0.0, blue / max_8_bit_int)));
        }
    }
    for (int32_t i = 0; i < image_matrix.size(); i++) {
        for (int32_t j = 0; j < image_matrix[i].size(); j++) {
            new_matrix[i][j].Green = 1.0 * new_matrix[i][j].Green / max_8_bit_int > threshold ? max_8_bit_int : 0;
            new_matrix[i][j].Red = 1.0 * new_matrix[i][j].Red / max_8_bit_int > threshold ? max_8_bit_int : 0;
            new_matrix[i][j].Blue = 1.0 * new_matrix[i][j].Blue / max_8_bit_int > threshold ? max_8_bit_int : 0;
        }
    }
    image_matrix = std::move(new_matrix);
}
