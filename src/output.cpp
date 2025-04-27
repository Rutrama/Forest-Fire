// output.cpp cuida da tarefa de salvar a matriz no arquivo de saída
#include "output.hpp"
#include <fstream>
#include <iostream> // remover depois

void Output::writeIteration(int iteration, const std::vector<std::vector<int>>& matrix, int AnimalX, int AnimalY) {
    std::ofstream file("./output.dat", std::ios::app); // Append to file

    if (file.is_open()) {
        file << "Iteração (" << iteration << "):\n";
        file << "Animal em (" << AnimalX << ", " << AnimalY << ")\n";
        for (const auto& row : matrix) {
            for (const auto& cell : row) {
                file << cell << " ";
            }
            file << "\n";
        }
        file << "\n"; // Empty line between iterations
        file.close();
    }
}

void Output::writeDeathInfo(int deathIteration) {
    std::ofstream file("./output.dat", std::ios::app); // Append to file

    if (file.is_open()) {
        if (deathIteration != -1) {
            file << "O animal morreu na iteração " << deathIteration << ".\n";
        } else {
            file << "O animal sobreviveu!\n";
        }
        file.close();
    }
}

void Output::printState(const std::vector<std::vector<int>>& matrix, int animalX, int animalY) const {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            if (i == animalX && j == animalY) std::cout << "A ";
            else std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}
