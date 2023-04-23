#include "GaussianBlur.h"

#include <cmath>
GaussianBlur::GaussianBlur(Image& image) : BaseFilter(image) {
}

double Gaussian(double x, double sigma) {
    return std::exp(-(std::pow(x, 2) / 2 / sigma / sigma)) / std::sqrt(2 * M_PI) / sigma;
}

void GaussianBlur::Apply(double sigma) {
    std::vector<double> kernel{};
    double sum = 0;
    const double sigma_coeff = 6;
    size_t kernel_size = static_cast<size_t>(std::abs(sigma_coeff * sigma)) + 1;
    for (ssize_t i = -(static_cast<ssize_t>(kernel_size) / 2); i < static_cast<ssize_t>(kernel_size) / 2; ++i) {
        double x = Gaussian(static_cast<double>(i), sigma);
        kernel.push_back(x);
        sum += x;
    }

    for (auto& elem : kernel) {
        elem /= sum;
    }
    auto& image_matrix = image.GetImageMatrix();
    for (int t = 0; t < 2; ++t) {
        std::vector<std::vector<Pixel>> new_matrix;
        new_matrix.resize(image_matrix.size(), std::vector<Pixel>(image_matrix[0].size(), Pixel{0, 0, 0}));

        for (size_t i = 0; i < image_matrix.size(); ++i) {
            for (size_t j = 0; j < image_matrix[i].size(); ++j) {

                auto square_size = static_cast<double>(kernel.size());
                double sum_red = 0;
                double sum_green = 0;
                double sum_blue = 0;
                auto left_border = static_cast<int64_t>(-square_size / 2);
                auto right_border = static_cast<int64_t>(square_size / 2);

                size_t index = 0;
                for (auto l = left_border; l < right_border; ++l) {
                    Pixel pixel;
                    if (!is_vertical_) {
                        pixel = image.Get(static_cast<int64_t>(i), static_cast<int64_t>(j + l));
                    } else {
                        pixel = image.Get(static_cast<int64_t>(i + l), static_cast<int64_t>(j));
                    }
                    sum_red += pixel.Red * kernel[index];
                    sum_green += pixel.Green * kernel[index];
                    sum_blue += pixel.Blue * kernel[index];
                    ++index;
                }
                new_matrix[i][j].Red = static_cast<int32_t>(sum_red);
                new_matrix[i][j].Green = static_cast<int32_t>(sum_green);
                new_matrix[i][j].Blue = static_cast<int32_t>(sum_blue);
            }
        }
        is_vertical_ = !is_vertical_;
        image_matrix = std::move(new_matrix);
    }
}
std::tuple<double, double, double> GaussianBlur::Matrix::ApplyMatrix(int32_t i, int32_t j) {
    {
        const double mc0 = matrix_coeffs[0];
        const double mc1 = matrix_coeffs[1];
        const double mc2 = matrix_coeffs[2];
        const double mc3 = matrix_coeffs[3];
        const double mc4 = matrix_coeffs[4];
        const double mc5 = matrix_coeffs[5];
        const double mc6 = matrix_coeffs[6];
        const double mc7 = matrix_coeffs[7];
        const double mc8 = matrix_coeffs[8];

        Pixel pixel0 = image_ref.Get(i - 1, j - 1);
        Pixel pixel1 = image_ref.Get(i - 1, j);
        Pixel pixel2 = image_ref.Get(i - 1, j + 1);
        Pixel pixel3 = image_ref.Get(i, j - 1);
        Pixel pixel4 = image_ref.Get(i, j);
        Pixel pixel5 = image_ref.Get(i, j + 1);
        Pixel pixel6 = image_ref.Get(i + 1, j - 1);
        Pixel pixel7 = image_ref.Get(i + 1, j);
        Pixel pixel8 = image_ref.Get(i + 1, j + 1);

        double sum_red = mc0 * pixel0.Red + mc1 * pixel1.Red + mc2 * pixel2.Red + mc3 * pixel3.Red + mc4 * pixel4.Red +
                         mc5 * pixel5.Red + mc6 * pixel6.Red + mc7 * pixel7.Red + mc8 * pixel8.Red;

        double sum_green = mc0 * pixel0.Green + mc1 * pixel1.Green + mc2 * pixel2.Green + mc3 * pixel3.Green +
                           mc4 * pixel4.Green + mc5 * pixel5.Green + mc6 * pixel6.Green + mc7 * pixel7.Green +
                           mc8 * pixel8.Green;

        double sum_blue = mc0 * pixel0.Blue + mc1 * pixel1.Blue + mc2 * pixel2.Blue + mc3 * pixel3.Blue +
                          mc4 * pixel4.Blue + mc5 * pixel5.Blue + mc6 * pixel6.Blue + mc7 * pixel7.Blue +
                          mc8 * pixel8.Blue;

        return std::make_tuple(sum_red, sum_green, sum_blue);
    }
}
