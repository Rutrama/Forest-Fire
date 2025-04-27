//setup.hpp
#pragma once
#include <vector>
#include <string>

struct SetupData {
    int rows;
    int cols;
    int fireX;
    int fireY;
    std::vector<std::vector<int>> matrix;
};

SetupData readSetup(const std::string& filename);