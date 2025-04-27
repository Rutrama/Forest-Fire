// grid.hpp

#include <vector>
#include "setup.hpp"
#include "fire.hpp"

class Grid {
private:
    std::vector<std::vector<int>> matrix;
    int animalX, animalY;
    bool animalAlive;
    int deathIteration;
    std::vector<std::pair<int, int>> getValidDirections (int animalX, int animalY);

public:
    Grid(const SetupData& data);

    void animalMove(int iteration);
    void checkAndUseWater();
    void handleFireImpact(int iteration);

    int getAnimalX() const;
    int getAnimalY() const;
    std::vector<std::vector<int>>& getMatrix();

    bool isAnimalDead() const;
    int getDeathIteration() const;
};
