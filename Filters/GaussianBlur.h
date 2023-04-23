#pragma once
#include "BaseFilter.h"

class GaussianBlur : public BaseFilter {
public:
    // NOLINTNEXTLINE
    inline static std::vector<double> coefficients_matrix = {};

    explicit GaussianBlur(Image& image);
    void Apply(double sigma) override;

    struct Matrix {

        Image& image_ref;
        std::vector<double> matrix_coeffs;

        explicit Matrix(Image& m, std::vector<double> matrix_coeffs)
            : image_ref{m}, matrix_coeffs(std::move(matrix_coeffs)) {
        }

        Pixel operator()(int64_t x, int64_t y) const {
            return image_ref.Get(x, y);
        }

        std::tuple<double, double, double> ApplyMatrix(int32_t i, int32_t j);
    };

private:
    bool is_vertical_ = true;
    std::vector<double> kernel_;
};
