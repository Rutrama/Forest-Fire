// output.hpp
#include <vector>
#include <string>

class Output {
public:
    void writeIteration(int iteration, const std::vector<std::vector<int>>& matrix, int AnimalX, int AnimalY);
    void writeDeathInfo(int deathIteration);
    void printState(const std::vector<std::vector<int>>& matrix, int animalX, int animalY) const; // auxilia em debugging de erros na matriz
};