add_executable(
        image_processor
        image_processor.cpp image.cpp Filters/CropFilter.cpp Filters/BaseFilter.cpp image.h Filters/NegativeFilter.h Filters/NegativeFilter.cpp Filters/GrayscaleFilter.h Filters/GrayscaleFilter.cpp Filters/SharpFilter.h Filters/SharpFilter.cpp Filters/EdgeFilter.cpp Filters/GaussianBlur.cpp Filters/SobelFilter.cpp Filters/SobelFilter.h Parser.cpp Parser.h)
