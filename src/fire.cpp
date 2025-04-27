//fire.cpp inclui as funções a serem executadas com a estrutura do incêndio, incluindo a atualização da matriz conforme o incêndio progride
#include "fire.hpp"
#include "config.hpp"
#include <algorithm> // for remove_if

using namespace std;

void Fire::addInitialFire(int x, int y) {
    burningTrees.push_back({x, y});
}

void Fire::spreadFrom(int x, int y, vector<vector<int>>& matrix, vector<pair<int, int>>& newFires) {
    vector<pair<int, int>> directions = getValidFireDirections(x, y, matrix.size(), matrix[0].size());

    for (auto dir : directions) {
        int nx = x + dir.first;
        int ny = y + dir.second;
        
        if (nx >= 0 && nx < matrix.size() && ny >= 0 && ny < matrix[0].size()) {
            if (matrix[nx][ny] == 1) { // Verifica árvore
                matrix[nx][ny] = 2; // Incendia árvore
                newFires.push_back({nx, ny});
            }
        }
    }
}

std::vector<std::pair<int, int>> Fire::getValidFireDirections(int x, int y, int rows, int cols) {
    std::vector<std::pair<int, int>> directions;
    
    // Limite N (y-1)
    if (y > 0 && (WIND == 0 || WIND == 1)) {
        directions.push_back({-1, 0});
    }
    // Limite S (y+1)
    if (y < cols - 1 && (WIND == 0 || WIND == 2)) {
        directions.push_back({1, 0});
    }
    // Limite W (x-1)
    if (x > 0 && (WIND == 0 || WIND == 3)) {
        directions.push_back({0, -1});
    }
    // Limite E (x+1)
    if (x < rows - 1 && (WIND == 0 || WIND == 4)) {
        directions.push_back({0, 1});
    }
    
    return directions;
}

void Fire::removeBurntTree(const std::pair<int, int>& tree) {
    burningTrees.erase(
        std::remove(burningTrees.begin(), burningTrees.end(), tree),
        burningTrees.end()
    );
}

void Fire::spreadFire(vector<vector<int>>& matrix) {
    if (burningTrees.empty()) return;

    vector<pair<int, int>> newFires;

    if (FAST_SPREAD) {
        for (auto& tree : burningTrees) {
            int x = tree.first;
            int y = tree.second;
            spreadFrom(x, y, matrix, newFires);
            matrix[x][y] = 3; // Modifica para Cinzas (3)
            removeBurntTree({x,y});
        }
    } else {
        if (!burningTrees.empty()) {
            auto tree = burningTrees[rand() % burningTrees.size()];
            int x = tree.first;
            int y = tree.second;
            spreadFrom(x, y, matrix, newFires);
            matrix[x][y] = 3; // Modifica para Cinzas (3)
            removeBurntTree({x,y});
        }
    }

    // Insere novos incêndios ao vetor
    burningTrees.insert(burningTrees.end(), newFires.begin(), newFires.end());
}