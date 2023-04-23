#include "image.h"

#include <iostream>
#include <vector>

Image::Image(const std::string& path) {
    Load(path);
}

void Image::Load(const std::string& path) {
    std::ifstream infile(path, std::ios::binary);
    if (!infile) {
        std::cout << "Failed to open file\n";
        throw std::invalid_argument("Failed to open file");
    }

    infile.read(reinterpret_cast<char*>(&bmp_header_), sizeof(bmp_header_));
    if (bmp_header_.signature[0] != 'B' || bmp_header_.signature[1] != 'M') {
        std::cout << "Invalid BMP signature\n";
        throw std::invalid_argument("Invalid BMP Signature.");
    }

    infile.read(reinterpret_cast<char*>(&dib_header_), sizeof(dib_header_));

    if (dib_header_.header_size != sizeof(DIBHeader) || dib_header_.bits_per_pixel != BMP_24_BITS ||
        dib_header_.compression_method != 0) {
        std::cout << "Invalid BMP format\n";
        throw std::invalid_argument("Invalid BMP format.");
    }

    infile.seekg(bmp_header_.data_offset, std::ios::beg);

    // определение размера отступа в конце каждой строки
    size_t line_padding = ((dib_header_.width * (dib_header_.bits_per_pixel / BITS_PER_BYTE)) % 4) & 3;

    // буффер для чтения
    unsigned char bufer = 0;

    std::vector<std::vector<Pixel>> new_image_matrix;
    new_image_matrix.reserve(dib_header_.height);
    for (size_t i = 0; i < dib_header_.height; i++) {
        std::vector<Pixel> pixels_row = {};
        pixels_row.reserve(dib_header_.width);
        for (size_t j = 0; j < dib_header_.width; j++) {
            auto pixel = Pixel{};

            infile.read(reinterpret_cast<char*>(&bufer), 1);
            pixel.Blue = bufer;
            infile.read(reinterpret_cast<char*>(&bufer), 1);
            pixel.Green = bufer;
            infile.read(reinterpret_cast<char*>(&bufer), 1);
            pixel.Red = bufer;
            pixels_row.push_back(pixel);
        }
        new_image_matrix.push_back(pixels_row);
        infile.seekg(static_cast<int64_t>(line_padding), std::ios_base::cur);
    }
    image_matrix_ = std::move(new_image_matrix);
}

void Image::Save(const std::string& path) {
    std::ofstream outfile(path, std::ios::binary);
    if (!outfile) {
        std::cerr << "Failed to create output file\n";
        throw std::invalid_argument("Failed to create output file.");
    }

    outfile.write(reinterpret_cast<char*>(&bmp_header_), sizeof(bmp_header_));
    outfile.write(reinterpret_cast<char*>(&dib_header_), sizeof(dib_header_));
    size_t line_padding = ((4 - (dib_header_.width * (dib_header_.bits_per_pixel / BITS_PER_BYTE)) % 4) & 3);
    outfile.seekp(bmp_header_.data_offset, std::ios::beg);
    for (size_t i = 0; i < dib_header_.height; i++) {
        for (size_t j = 0; j < dib_header_.width; j++) {
            outfile.write(reinterpret_cast<char*>(&image_matrix_[i][j].Blue), 1);
            outfile.write(reinterpret_cast<char*>(&image_matrix_[i][j].Green), 1);
            outfile.write(reinterpret_cast<char*>(&image_matrix_[i][j].Red), 1);
        }
        for (size_t k = 0; k < line_padding; k++) {
            unsigned char temp = 0;
            outfile.write(reinterpret_cast<char*>(&temp), 1);
        }
    }
}
void Image::UpdateSize() {
    bmp_header_.file_size = bmp_header_.data_offset + dib_header_.image_size;
    dib_header_.image_size = dib_header_.width * dib_header_.height * dib_header_.bits_per_pixel / BITS_PER_BYTE;
}

int32_t Image::GetImageWidth() const {
    return dib_header_.width;
}
int32_t Image::GetImageHeight() const {
    return dib_header_.height;
}

void Image::SetImageWidth(int32_t new_width) {
    dib_header_.width = new_width;
    UpdateSize();
}
void Image::SetImageHeight(int32_t new_height) {
    dib_header_.height = new_height;
    UpdateSize();
}
std::vector<std::vector<Pixel>>& Image::GetImageMatrix() {
    return image_matrix_;
}

Image::Image() {
}

Pixel Image::Get(int64_t x, int64_t y) {
    if (x >= image_matrix_.size() || x < 0 || y >= image_matrix_.at(0).size() || y < 0) {
        if (x < 0) {
            x = 0;
        } else if (x >= image_matrix_.size()) {
            x = static_cast<int64_t>(image_matrix_.size() - 1);
        }
        if (y < 0) {
            y = 0;
        } else if (y >= image_matrix_.at(0).size()) {
            y = static_cast<int64_t>(image_matrix_.at(0).size() - 1);
        }
    }
    return image_matrix_[std::abs(x)][std::abs(y)];
}
