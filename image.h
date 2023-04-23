#pragma once
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#pragma pack(push, 1)  // pack structures tightly

int const BITS_PER_BYTE = 8;
int const BMP_24_BITS = 24;

struct BMPHeader {
    char signature[2];
    uint32_t file_size;
    uint16_t reserved_1;
    uint16_t reserved_2;
    uint32_t data_offset;
};

struct DIBHeader {
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t num_color_planes;
    uint16_t bits_per_pixel;
    uint32_t compression_method;
    uint32_t image_size;
    int32_t horizontal_resolution;
    int32_t vertical_resolution;
    uint32_t num_colors_in_palette;
    uint32_t num_important_colors;
};
#pragma pack(pop)

struct Pixel {
    int32_t Blue;
    int32_t Green;
    int32_t Red;
};

class Image {
public:
    explicit Image(const std::string& path);

    void Load(const std::string& path);

    void Save(const std::string& path);

    std::vector<std::vector<Pixel>>& GetImageMatrix();

    Pixel Get(int64_t x, int64_t y);

    void SetImageWidth(int32_t new_width);
    void SetImageHeight(int32_t new_height);
    [[nodiscard]] int32_t GetImageWidth() const;
    [[nodiscard]] int32_t GetImageHeight() const;

    void UpdateSize();

    Image();

private:
    BMPHeader bmp_header_{};
    DIBHeader dib_header_{};
    std::vector<std::vector<Pixel>> image_matrix_;
};