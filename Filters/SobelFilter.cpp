#include "SobelFilter.h"

#include "GaussianBlur.h"

void SobelFilter::Apply() {
    const std::vector<double> matrix_coeffs = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    const std::vector<double> matrix_coeffs2 = {-1, 0, 1, -2, 0, 2, -1, 0, 1};

    auto m = GaussianBlur::Matrix{(image), matrix_coeffs};

    auto image_matrix = image.GetImageMatrix();
    const int max_8_bit_int = 255;
    std::vector<std::vector<Pixel>> new_matrix;
    new_matrix.resize(image_matrix.size(), std::vector<Pixel>(image_matrix[0].size(), Pixel{0, 0, 0}));
    for (int32_t i = 0; i < image_matrix.size(); i++) {
        for (int32_t j = 0; j < image_matrix[0].size(); j++) {

            auto [red, green, blue] = m.ApplyMatrix(i, j);

            new_matrix[i][j].Red =
                static_cast<int32_t>(max_8_bit_int * std::min(1.0, std::max(0.0, red / max_8_bit_int)));
            new_matrix[i][j].Green =
                static_cast<int32_t>(max_8_bit_int * std::min(1.0, std::max(0.0, green / max_8_bit_int)));
            new_matrix[i][j].Blue =
                static_cast<int32_t>(max_8_bit_int * std::min(1.0, std::max(0.0, blue / max_8_bit_int)));
        }
    }
    image_matrix = std::move(new_matrix);

    auto m2 = GaussianBlur::Matrix{(image), matrix_coeffs2};

    std::vector<std::vector<Pixel>> new_matrix2;
    new_matrix2.resize(image_matrix.size(), std::vector<Pixel>(image_matrix[0].size(), Pixel{0, 0, 0}));
    for (int32_t i = 0; i < image_matrix.size(); i++) {
        for (int32_t j = 0; j < image_matrix[0].size(); j++) {

            auto [red, green, blue] = m2.ApplyMatrix(i, j);

            new_matrix2[i][j].Red =
                static_cast<int32_t>(max_8_bit_int * std::min(1.0, std::max(0.0, red / max_8_bit_int)));
            new_matrix2[i][j].Green =
                static_cast<int32_t>(max_8_bit_int * std::min(1.0, std::max(0.0, green / max_8_bit_int)));
            new_matrix2[i][j].Blue =
                static_cast<int32_t>(max_8_bit_int * std::min(1.0, std::max(0.0, blue / max_8_bit_int)));
        }
    }
    image_matrix = std::move(new_matrix2);
}
SobelFilter::SobelFilter(Image& image) : BaseFilter(image) {
}
