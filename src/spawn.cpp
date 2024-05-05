#include "Engine.h"

void Engine::spawnPlayer() {
    /*
        @return void

        Spawns player
        -Sets a position
    */

    //this->player.setPosition(
    //        (static_cast<float>(1 + this->positionHelper.x)) * 100.f,
    //        (static_cast<float>(1 + this->positionHelper.y)) * 100.f
    //);

    this->player.setPosition(this->startingPosition);
}

void Engine::spawnEnemy() {
    /*
        @return void

        Spawns enemies and sets their positions
        -Sets a random position
        -Adds enemy to the vector
    */

    this->enemy.setPosition(280.f, 280.f);
}

void Engine::spawnKeys() {
    /*
        @return void

        Spawns keys and sets their positions
        -Sets a random position
        -Adds key to the vector
    */
    this->keys.clear();
    this->visibleKeys.clear();

    for (int i = 0; i < this->numberKeys; ++i) {
        Vector2f keyTile;
        do {
            keyTile = getRandomTile();
        } while (isForbidden(keyTile));

        // Sets the key's position and the keys list
        this->key.setPosition(keyTile);
        this->keys.push_back(this->key);
        this->visibleKeys.push_back(false);

        // add the previous key's position to the forbidden tiles
        this->forbiddenTiles.push_back(keyTile);
    }
}

void Engine::resetDoors() {
    /*
        @return void

        Close all the doors
    */

    for (int i = 0; i < this->vDoors.size(); ++i) {
        for (int j = 0; j < this->vDoors[i].size(); ++j) {
            if (!(i==0 && j==0)) {
                this->closeDoor({i, j}, "vertical");
            }
        }
    }
    for (int i = 0; i < this->hDoors.size(); ++i) {
        for (int j = 0; j < this->hDoors[i].size(); ++j) {
            if (!(i==0 && j==0)) {
                this->closeDoor({i, j}, "horizontal");
            }
        }
    }
}

void Engine::spawnEntities() {
    this->spawnPlayer();
    this->spawnEnemy();
    this->spawnKeys();
}