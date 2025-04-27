//setup.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "config.hpp"

using namespace std;

struct Field {
    int rows;
    int cols;
    int fireX;
    int fireY;
    vector<vector<int>> matrix;
};

Field readSetup(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    Field data;
    infile >> data.rows >> data.cols >> data.fireX >> data.fireY;

    data.matrix.resize(data.rows, vector<int>(data.cols));

    for (int i = 0; i < data.rows; ++i) {
        for (int j = 0; j < data.cols; ++j) {
            infile >> data.matrix[i][j];
        }
    }

    infile.close();

    return data;
}