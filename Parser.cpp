#include "Parser.h"

#include <utility>

#include "Filters/CropFilter.h"
#include "Filters/EdgeFilter.h"
#include "Filters/GaussianBlur.h"
#include "Filters/GrayscaleFilter.h"
#include "Filters/NegativeFilter.h"
#include "Filters/SharpFilter.h"
#include "Filters/SobelFilter.h"
#include "image.h"

bool Parser::ParseInput() {
    std::string input_path = argv_[1];
    std::string output_path = argv_[2];
    Image image;
    try {
        image = Image(input_path);
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
    }

    for (int i = 3; i < argc_; ++i) {
        std::string filter_name = argv_[i];
        if (filter_name == "-crop") {
            int width = std::stoi(argv_[i + 1]);
            int height = std::stoi(argv_[i + 2]);
            ++i;
            ++i;
            CropFilter filter(image);
            width = std::min(width, image.GetImageWidth());
            height = std::min(height, image.GetImageHeight());
            filter.Apply(width, height);
            image.SetImageWidth(width);
            image.SetImageHeight(height);
        } else if (filter_name == "-neg") {
            NegativeFilter filter(image);
            filter.Apply();

        } else if (filter_name == "-gs") {
            GrayscaleFilter filter(image);
            filter.Apply();

        } else if (filter_name == "-sharp") {
            SharpFilter filter(image);
            filter.Apply();

        } else if (filter_name == "-edge") {
            double threshold = std::stod(argv_[i + 1]);
            ++i;
            GrayscaleFilter filter_gray(image);
            filter_gray.Apply();
            EdgeFilter filter(image);
            filter.Apply(threshold);

        } else if (filter_name == "-blur") {
            double sigma = std::stod(argv_[i + 1]);
            ++i;
            GaussianBlur filter(image);
            filter.Apply(sigma);
        } else if (filter_name == "-sobel") {
            GrayscaleFilter filter(image);
            filter.Apply();
            SobelFilter filter2(image);
            filter2.Apply();
        } else {
            std::cerr << "No such filter: " << filter_name << "\n";
            break;
        }
    }
    try {
        image.Save(output_path);
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
    }
    return true;
}
Parser::Parser(int argc, std::vector<std::string> argv) : argc_{argc}, argv_{std::move(argv)} {
}