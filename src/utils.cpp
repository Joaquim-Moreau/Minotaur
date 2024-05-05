#include "Engine.h"

bool Engine::isMovePossible(const Sprite &entity, const string & direction) {
    /*
     *@return bool
     *
     * Check if a movement is possible.
     * ie: if the entity stays inside the labyrinth
     */

    Vector2f vecDirection;
    if (direction == "Left") {
        vecDirection = Vector2f (-100.f, 0.f);
    } else if (direction == "Down") {
        vecDirection = Vector2f (0.f, 100.f);
    } else if (direction == "Right") {
        vecDirection = Vector2f (100.f, 0.f);
    } else if (direction == "Up") {
        vecDirection = Vector2f (0.f, -100.f);
    }

    bool possible = false;
    Vector2f nextPos = entity.getPosition() + vecDirection;
    if (50.f < nextPos.x  && nextPos.x < 550.f
     && 50.f < nextPos.y  && nextPos.y < 550.f) {
        possible = true;
    }
    return possible;
}

bool Engine::isDoorOpen(const Sprite &entity, const string & direction) {
    /*
     *@return bool
     *
     * Check if the door is open
     */
    bool result = false;
    Vector2i doorID = getDoorID(entity, direction);
    if (direction == "Up" || direction == "Down"){
        if (this->isHDoorOpen[doorID.x][doorID.y]) {
            result = true;
        }
    } else if (direction == "Left" || direction == "Right") {
        if (this->isVDoorOpen[doorID.x][doorID.y]) {
            result = true;
        }
    }
    return result;
}

bool Engine::isThereADoor(const Sprite &entity, const string& direction) {
    /*
     *@return bool
     *
     * Check if there is a door in the desired direction
     */

    Vector2f position = this->convertPosition(entity);
    bool result = false;
    if (direction == "Left") {
        if (position.x > 0.f) {
            if (position != Vector2f(1.f, 0.f)) {
                result = true;
            }
        }
    } else if (direction == "Right") {
        if (position.x < 4.f) {
            if (position != Vector2f(0.f, 0.f)) {
                result = true;
            }
        }
    } else if (direction == "Up") {
        if (position.y > 0.f) {
            if (position != Vector2f(0.f, 1.f)){
                result = true;
            }
        }
    } else if (direction == "Down") {
        if (position.y < 4.f) {
            if (position != Vector2f(0.f, 0.f)){
                result = true;
            }
        }
    }
    return result;
}

Vector2i Engine::getDoorID(const Sprite &entity, const string& direction) {
    /*
     *@return Vector2i.
     *
     * Returns the ID of the door in the desired direction.
     * The ID will be used in doors vector.
     */
    Vector2f position = this->convertPosition(entity);
    Vector2i result;
    if (direction == "Left") {
        if (position.x > 0.f) {
            if (position != Vector2f(1.f, 0.f)) {
                // Vertical doors
                result = { static_cast<int>(position.x - 1.f),
                           static_cast<int>(position.y)};
            }
        }
    } else if (direction == "Right") {
        if (position.x < 4.f) {
            if (position != Vector2f(0.f, 0.f)) {
                // Vertical doors
                result = { static_cast<int>(position.x),
                           static_cast<int>(position.y)};
            }
        }
    } else if (direction == "Up") {
        if (position.y > 0.f) {
            if (position != Vector2f(0.f, 1.f)){
                // Horizontal doors
                result = { static_cast<int>(position.x),
                           static_cast<int>(position.y - 1.f)};
            }
        }
    } else if (direction == "Down") {
        if (position.y < 4.f) {
            if (position != Vector2f(0.f, 0.f)){
                // Horizontal doors
                result = { static_cast<int>(position.x),
                           static_cast<int>(position.y)};
            }
        }
    }
    return result;
}

bool Engine::isForbidden(Vector2f position) {
    /*
     *@return bool.
     *
     * Indicates if a tile is forbidden for a key to spawn
     */

    for (const auto & forbiddenTile : forbiddenTiles) {
        if (position.x == forbiddenTile.x && position.y == forbiddenTile.y) {
            return true;
        }
    }
    return false;
}

Vector2f Engine::getRandomTile() {
    /*
     *@return Vector2f.
     *
     * Returns the position of a tile selected randomly
     */
    float xKey = (static_cast<float>(rand() % 5)*100) + 80.f;
    float yKey = (static_cast<float>(rand() % 5)*100) + 80.f;
    return {xKey, yKey};
}

Vector2f Engine::convertPosition(const Sprite &entity) {
    /*
     *@return Vector2f.
     *
     * Converts the position of an entity from pixels to IDs
     */
    return {(entity.getPosition().x - this->startingPosition.x) / 100.f,
            (entity.getPosition().y - this->startingPosition.y) / 100.f};
}

bool Engine::comparePosition(const Sprite &entity1, const Sprite &entity2) {
    /*
     *@return bool.
     *
     * Return true if the two entities are in the same tile
     */
    return (convertPosition(entity1) == convertPosition(entity2));
}

bool Engine::isAligned(const Sprite &entity1, const Sprite &entity2) {
    /*
     *@return bool.
     *
     * Return true if the two entities are aligned
     */
    return (convertPosition(entity1).x == convertPosition(entity2).x ||
            convertPosition(entity1).y == convertPosition(entity2).y);
}


