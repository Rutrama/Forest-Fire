//fire.hpp inclui a estrutura da classe que representa o incêndio além das funções que podem ser chamadas de fire.cpp
#include <vector>
#include <utility>

class Fire {
private:
    void spreadFrom(int x, int y, std::vector<std::vector<int>>& matrix, std::vector<std::pair<int, int>>& newFires);
    std::vector<std::pair<int, int>> getValidFireDirections (int nx, int ny, int sizeX, int sizeY);
    static std::vector<std::pair<int, int>> burningTrees;

public:
    Fire() = default;
    void static removeBurntTree(const std::pair<int, int>& tree);
    void addInitialFire(int x, int y);
    void spreadFire(std::vector<std::vector<int>>& matrix);
    bool hasActiveFire() const { return !burningTrees.empty(); }
};