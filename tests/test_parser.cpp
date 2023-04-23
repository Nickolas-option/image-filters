#include <catch.hpp>

#include "../Parser.h"

TEST_CASE("ParseInput") {
    // NOLINTBEGIN
    //  Test ParseInput() with valid input
    std::vector<std::string> argv_valid = {"image_processor.cpp",
                                           "C:/Users/nikae/CLionProjects/pmi-229-2-Nikolas-Evkarpidi-Another_option/"
                                           "tasks/image_processor/test_script/data/lenna.bmp",
                                           "test.bmp",
                                           "-crop",
                                           "200",
                                           "300"};
    Parser parser{7, argv_valid};
    REQUIRE(parser.ParseInput() == true);

    // Test ParseInput() with invalid input
    std::vector<std::string> argv_invalid = {"image_processor.cpp",
                                             "C:/Users/nikae/CLionProjects/pmi-229-2-Nikolas-Evkarpidi-Another_option/"
                                             "tasks/image_processor/test_script/data/lenna_BLA_BLA.bmp"};
    Parser parser2{2, argv_invalid};

    REQUIRE_THROWS_AS(parser.ParseInput(), std::invalid_argument);

    // Test that filters are applied correctly
    std::vector<std::string> argv_filters = {"image_processor.cpp",
                                             "C:/Users/nikae/CLionProjects/pmi-229-2-Nikolas-Evkarpidi-Another_option/"
                                             "tasks/image_processor/test_script/data/lenna.bmp",
                                             "test.bmp", "-neg"};
    Parser parser3{4, argv_filters};
    REQUIRE(parser.ParseInput() == true);

    // Test that invalid filters are handled correctly
    std::vector<std::string> argv_invalid_filters = {
        "image_processor.cpp",
        "C:/Users/nikae/CLionProjects/pmi-229-2-Nikolas-Evkarpidi-Another_option/tasks/image_processor/test_script/"
        "data/lenna.bmp",
        "test.bmp", "-invalid_filter"};

    Parser parser4{5, argv_invalid_filters};
    REQUIRE_THROWS_AS(parser.ParseInput(), std::invalid_argument);
}
// NOLINTEND