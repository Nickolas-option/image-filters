#pragma once

#include <string>
#include <vector>
class Parser {
public:
    Parser(int argc, std::vector<std::string> argv);
    bool ParseInput();

private:
    int argc_;
    std::vector<std::string> argv_;
};
