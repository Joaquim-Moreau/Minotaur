#include "Engine.h"

int main() {
    // init random
    srand(static_cast<unsigned> (time(NULL)));

    // init game engine
    Engine engine;

    // Game loop
    // Spawn entities
    engine.spawnEntities();

    while (engine.getWindowIsOpen()) {
        engine.run();
    }

    return 0;
}
