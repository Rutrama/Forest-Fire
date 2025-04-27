//grid.cpp é a estrutura da matriz onde ocorre a simulação além das interações do animal
#include "grid.hpp"
#include "config.hpp"
#include "fire.hpp"
#include <iostream>

Grid::Grid(const SetupData& data) 
    : matrix(data.matrix), animalX(ANIMAL_START_POSITION.first), animalY(ANIMAL_START_POSITION.second), animalAlive(true), deathIteration(-1)
{}

int Grid::getAnimalX() const {
    return animalX;
}

int Grid::getAnimalY() const {
    return animalY;
}

std::vector<std::pair<int, int>> Grid::getValidDirections (int nx, int ny) {
    std::vector<std::pair<int, int>> directions;
    if (nx > 0) {
        directions.push_back({-1,0});
    }
    if (nx < ((matrix.size())-1)) {
        directions.push_back({1,0});
    }
    if (ny > 0) {
        directions.push_back({0,-1});
    }
    if (ny < ((matrix[0].size())-1)) {
        directions.push_back({0,1});
    }
    return directions;
}

void Grid::animalMove(int iteration) {
    if (!animalAlive) return;

    std::vector<std::pair<int, int>> directions = getValidDirections (animalX, animalY);
    std::vector<std::pair<int, int>> safeMoves;

    for (auto dir : directions) {
        int nx = animalX + dir.first;
        int ny = animalY + dir.second;

            int tile = matrix[nx][ny];
            if (tile == 4) safeMoves.push_back({nx, ny});
            else if (tile == 1) safeMoves.push_back({nx, ny});
            else if (tile == 0) safeMoves.push_back({nx, ny});
            else if (tile == 3 && matrix[animalX][animalY] != 2) safeMoves.push_back({nx, ny});
    }

    if (!(safeMoves.empty())) {
        auto move = safeMoves[0];
        animalX = move.first;
        animalY = move.second;
    }
    else {
        animalAlive = false;
        deathIteration = iteration;
    }
}

void Grid::checkAndUseWater() {
    if (!animalAlive) return;
    if (matrix[animalY][animalX] != 4) return;

    std::vector<std::pair<int, int>> directions = getValidDirections (animalX, animalY);

    for (auto dir : directions) {
        int nx = animalY + dir.first;
        int ny = animalX + dir.second;
        if (matrix[nx][ny] == 2) {
        Fire::removeBurntTree({nx, ny});
        }
        matrix[nx][ny] = 1; // Water creates a forest surrounding the animal
    }
    matrix[animalY][animalX] = 0; // All the water was used
}

void Grid::handleFireImpact(int iteration) {
    if (!animalAlive) return;

    if (matrix[animalX][animalY] == 2) { // Fire reached animal
        // Emergency move
        std::cout << "Animal pegou fogo em: (" << animalX << "," << animalY << "\n";
        animalMove(iteration);
    }
}

std::vector<std::vector<int>>& Grid::getMatrix() {
    return matrix;
}

bool Grid::isAnimalDead() const {
    return !animalAlive;
}

int Grid::getDeathIteration() const {
    return deathIteration;
}