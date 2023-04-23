#include <iostream>

#include "Filters/CropFilter.h"
#include "Filters/EdgeFilter.h"
#include "Filters/GaussianBlur.h"
#include "Filters/GrayscaleFilter.h"
#include "Filters/NegativeFilter.h"
#include "Filters/SharpFilter.h"
#include "Filters/SobelFilter.h"
#include "image.h"
#include "Parser.h"
int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0]
                  << " input_image.bmp output_image.bmp (filters with " -
                         " and their "
                         "parameter(-s) \n"
                  << "Example: input.bmp output.bmp -blur 3 -crop "
                     "500 500 -sharp";
        std::cerr << "All filters that are available: -crop x y, -edge x, -blur x, -gs, -neg, -sharp, -sobel";
        return 1;
    }
    std::vector<std::string> argv_new;
    argv_new.reserve(argc);
    for (int i = 0; i < argc; i++) {
        argv_new.emplace_back(argv[i]);
    }

    Parser parser(argc, argv_new);
    parser.ParseInput();
    return 0;
}
