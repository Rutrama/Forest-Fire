#include "setup.hpp"
#include "config.hpp"
#include "grid.hpp"
#include "fire.hpp"
#include "output.hpp"

int main() {
    SetupData data = readSetup("./input.dat");
    Grid grid(data);
    Fire fire;
    Output output;

    fire.addInitialFire(data.fireX, data.fireY);

    output.writeIteration(0, grid.getMatrix(), grid.getAnimalX(), grid.getAnimalY());

    for (int iteration = 1; iteration <= MAX_ITERATIONS; ++iteration) {
        grid.animalMove( iteration );

        grid.checkAndUseWater();

        fire.spreadFire(grid.getMatrix());

        grid.handleFireImpact(iteration);

        output.writeIteration(iteration, grid.getMatrix(), grid.getAnimalX(), grid.getAnimalY());

        if (!fire.hasActiveFire()) {
            break;
        }
    }

    output.writeDeathInfo(grid.getDeathIteration());

    return 0;
}