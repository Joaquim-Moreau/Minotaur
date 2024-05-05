#include "Engine.h"

void Engine::updateWindow() {
    /*
     * @return void
     *
     * Close the window when the "escape" key is pressed
     * or when clicking the exit x
     */

    switch (this->event.type) {
        case Event::Closed:
            this->window->close();
            break;
        case Event::KeyPressed:
            if (this->event.key.code == Keyboard::Escape) {
                this->window->close();
            }
            break;
        default:
            break;
    }
}

void Engine::updateTurns() {
    /*
     * @return void
     *
     * -If the player has no movement and actions left, end turn
     * -If the minotaur has no movement left, end turn
     */

    if ((this->playerMovementLeft <= 0 && this->actionsLeft <=0 && myTurn)){
        this->myTurn = false;
        this->enemyMovementLeft = enemyMovement;
    }
    if (this->enemyMovementLeft <= 0 && !myTurn){
        this->myTurn = true;
        this->playerMovementLeft = playerMovement;
        this->actionsLeft = actions;
    }
}

void Engine::updateMousePosition() {
    /*
     * @return void
     *
     * get the mouse position
     */

    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Engine::updatePlayer() {
    /*
     * @return void
     *
     * Manage the player's turn
     *
     * -End turn when pressing F
     * -Pull a lever to change the door configuration
     * -Move around when pressing the arrow keys
     */

    switch (this->event.type) {
        case Event::KeyPressed:
            // End turn
            if (this->event.key.code == Keyboard::F) {
                this->myTurn = false;
                this->pullingLever = false;
                this->enemyMovementLeft = enemyMovement;
            }

            // Actions
            if (this->pullingLever) {
                // Press space to go into "movement mode"
                if (this->event.key.code == Keyboard::Space) {
                    this->pullingLever = false;
                }

                // Press an arrow key to pull the associated lever to change the doors
                if (this->event.key.code == Keyboard::Down) {
                    const string direction = "Down";
                    this->player.setTexture(this->playerTextureFront);
                    pullLever(this->helper, direction);
                }

                if (this->event.key.code == Keyboard::Left) {
                    const string direction = "Left";
                    this->player.setTexture(this->playerTextureLeft);
                    pullLever(this->helper, direction);
                }

                if (this->event.key.code == Keyboard::Up) {
                    const string direction = "Up";
                    this->player.setTexture(this->playerTextureBack);
                    pullLever(this->helper, direction);
                }

                if (this->event.key.code == Keyboard::Right) {
                    const string direction = "Right";
                    this->player.setTexture(this->playerTextureRight);
                    pullLever(this->helper, direction);
                }

            // Movements
            } else {
                if (this->playerMovementLeft) {
                    // Press an arrow key to move to the associated room if it's possible
                    // ie: if there is no wall, and if the door is open
                    if (this->event.key.code == Keyboard::Down) {
                        string direction = "Down";
                        if (isThereADoor(this->player, direction)) {
                            if (isDoorOpen(this->player, direction)) {
                                moveEntity(this->player, direction);
                                this->player.setTexture(this->playerTextureFront);
                                this->playerMovementLeft-=1;
                            }
                        } else {
                            if (isMovePossible(this->player, direction)) {
                                moveEntity(this->player, direction);
                                this->player.setTexture(this->playerTextureFront);
                                this->playerMovementLeft-=1;
                            }
                        }
                    }

                    if (this->event.key.code == Keyboard::Left) {
                        string direction = "Left";
                        if (isThereADoor(this->player, direction)) {
                            if (isDoorOpen(this->player, direction)) {
                                moveEntity(this->player, direction);
                                this->player.setTexture(this->playerTextureLeft);
                                this->playerMovementLeft-=1;
                            }
                        } else {
                            if (isMovePossible(this->player, direction)) {
                                moveEntity(this->player, direction);
                                this->player.setTexture(this->playerTextureLeft);
                                this->playerMovementLeft-=1;
                            }
                        }
                    }

                    if (this->event.key.code == Keyboard::Up) {
                        string direction = "Up";
                        if (isThereADoor(this->player, direction)) {
                            if (isDoorOpen(this->player, direction)) {
                                moveEntity(this->player, direction);
                                this->player.setTexture(this->playerTextureBack);
                                this->playerMovementLeft-=1;
                            }
                        } else {
                            if (isMovePossible(this->player, direction)) {
                                moveEntity(this->player, direction);
                                this->player.setTexture(this->playerTextureBack);
                                this->playerMovementLeft-=1;
                            }
                        }
                    }

                    if (this->event.key.code == Keyboard::Right) {
                        string direction = "Right";
                        if (isThereADoor(this->player, direction)) {
                            if (isDoorOpen(this->player, direction)) {
                                moveEntity(this->player, direction);
                                this->player.setTexture(this->playerTextureRight);
                                this->playerMovementLeft-=1;
                            }
                        } else {
                            if (isMovePossible(this->player, direction)) {
                                moveEntity(this->player, direction);
                                this->player.setTexture(this->playerTextureRight);
                                this->playerMovementLeft-=1;
                            }
                        }
                    }

                    // Return starting position
                    if (this->event.key.code == Keyboard::Tab &&
                    this->player.getPosition() != this->startingPosition) {
                        this->player.setPosition(this->startingPosition);
                        this->playerMovementLeft-=1;
                    }
                }

                // Press space to go into "action mode"
                if (this->event.key.code == Keyboard::Space && this->actionsLeft > 0) {
                    this->pullingLever = true;
                    this->helper.setPosition(this->player.getPosition());
                }
            }
        default:
            break;
    }
}

void Engine::updateEnemies() {
    /*
     *@return void
     *
     * Manage the minotaur's turn
     * Make him moves randomly on the map
     * -If the door is open, it costs 1 movement point
     * -If the door is closed, it costs 2 movement points and opens the door
     */

    // Choose a random direction
    int randDirection = rand()%4+1;
    string direction;
    string orientation;
    if (randDirection==1) {
        direction = "Left";
        orientation = "vertical";
        this->enemy.setTexture(this->minotaurTextureLeft);
    }
    if (randDirection==2) {
        direction = "Up";
        orientation = "horizontal";
        this->enemy.setTexture(this->minotaurTextureBack);
    }
    if (randDirection==3) {
        direction = "Right";
        orientation = "vertical";
        this->enemy.setTexture(this->minotaurTextureRight);
    }
    if (randDirection==4) {
        direction = "Down";
        orientation = "horizontal";
        this->enemy.setTexture(this->minotaurTextureFront);
    }

    // If the given direction doesn't get you out of the map
    if (isMovePossible(this->enemy, direction)) {
        // If there is a closed door, then movement costs 2 else it costs 1
        if (isThereADoor(this->enemy, direction) && !isDoorOpen(this->enemy, direction)){
            if (this->enemyMovementLeft == 2) {
                openDoor(getDoorID(this->enemy, direction), orientation);
                moveEntity(this->enemy, direction);

                this->enemyMovementLeft -= 2;
            }
        } else {
            moveEntity(this->enemy, direction);
            this->enemyMovementLeft-=1;
        }
    }
}

// Update doors
void Engine::openDoor(Vector2i doorID, const string & orientation) {
    /*
     *@return void
     *
     * 0pen the door
     */

    changeDoorColor(doorID, orientation, Color::Green);
    if (orientation=="horizontal") {
        this->isHDoorOpen[doorID.x][doorID.y] = true;
    } else if (orientation=="vertical") {
        this->isVDoorOpen[doorID.x][doorID.y] = true;
    } else {
        cout << "error open door";
    }
}

void Engine::closeDoor(Vector2i doorID, const string & orientation) {
    /*
     *@return void
     *
     * Close the door
     */

    changeDoorColor(doorID, orientation, Color::Red);
    if (orientation=="horizontal") {
        this->isHDoorOpen[doorID.x][doorID.y] = false;
    } else if (orientation=="vertical") {
        this->isVDoorOpen[doorID.x][doorID.y] = false;
    } else {
        cout << "error close door";
    }
}

void Engine::changeDoorColor(Vector2i doorID, const string& orientation, Color color) {
    /*
     *@return void
     *
     * Change the given door to the desired color
     */

    if (orientation=="horizontal") {
        this->hDoors[doorID.x][doorID.y].setFillColor(color);
    } else if (orientation=="vertical") {
        this->vDoors[doorID.x][doorID.y].setFillColor(color);
    } else {
        cout << "error change door";
    }
}

void Engine::pullLever(Sprite &entity, const string & direction) {
    /*
     *@return void
     *
     * Execute all the actions linked to pulling a lever.
     * ie: close the door, then in the next room, close the perpendicular doors
     * if they are opened and opens them if they are closed.
     */

    string firstOrientation;
    string secondOrientation;
    string firstDirectionNextRoom;
    string secondDirectionNextRoom;
    if (direction == "Left" || direction == "Right") {
        firstOrientation = "vertical";
        secondOrientation = "horizontal";
        firstDirectionNextRoom = "Up";
        secondDirectionNextRoom = "Down";
    } else if (direction == "Down" || direction == "Up") {
        firstOrientation = "horizontal";
        secondOrientation = "vertical";
        firstDirectionNextRoom = "Left";
        secondDirectionNextRoom = "Right";
    }

    // check if there is a door in the direction you want
    bool firstDoor = isThereADoor(entity, direction);

    if (firstDoor) {

        // if there is, the helper closes the door
        Vector2i firstDoorID = getDoorID(entity,  direction);
        closeDoor(firstDoorID, firstOrientation);

        // and we resolve the player's state
        this->pullingLever = false;
        //this->player.setOutlineColor(Color::Black);
        this->actionsLeft -= 1;

        // Then the helper moves to the next room
        moveEntity(entity, direction);

        // and if it's possible he will change the perpendicular doors
        // if it's open, close it and if it's closed, open it
        if (isThereADoor(entity, firstDirectionNextRoom)) {
            Vector2i firstDoorNextRoomID = getDoorID(entity, firstDirectionNextRoom);

            if (isDoorOpen(entity, firstDirectionNextRoom)) {
                closeDoor(firstDoorNextRoomID, secondOrientation);
            }
            else {
                openDoor(firstDoorNextRoomID, secondOrientation);
            }
            // changeDoorColor(firstDoorNextRoomID, secondOrientation, Color::Green);
        }

        if (isThereADoor(entity, secondDirectionNextRoom)) {
            Vector2i secondDoorNextRoomID = getDoorID(entity, secondDirectionNextRoom);

            if (isDoorOpen(entity, secondDirectionNextRoom)) {
                closeDoor(secondDoorNextRoomID, secondOrientation);
            }
            else {
                openDoor(secondDoorNextRoomID, secondOrientation);
            }
            //changeDoorColor(secondDoorNextRoomID, secondOrientation, Color::Green);
        }
    }
}

void Engine::moveEntity(Sprite &entity, const string& direction) {
    /*
     *@return void
     *
     * Move the entity in the desired direction
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

    if (isMovePossible(entity, direction)) {
        entity.move(vecDirection);
    }
}

// Update keys
void Engine::updateKeys() {
    /*
     *@return void
     *
     * Manage the keys.
     * The keys are invisible at spawn
     * -If the player is aligned with a key, reveal the key
     * -If the player is on the same tile as a key, delete the key and give 1 point to the player
     */

    for (int i = 0; i < this->keys.size(); i++){
        if (isAligned(this->player, this->keys[i])) {
            this->visibleKeys[i] = true;
        }
        if (comparePosition(this->player, this->keys[i])) {
            this->keys.erase(this->keys.begin() + i);
            this->points+=1;
        }
    }
}

void Engine::updateText() {
    /*
     *@return void
     *
     * Manage the text
     * For the game over screen, above and on the buttons if the game is over
     * or on top of the board if the game is ongoing
     */

    if (gameOver) {
        stringstream ss1;
        if (victory) {
            ss1 << "GG Well played !";
        } else {
            ss1 << "Maybe next time";
        }
        this->gameOverText1.setPosition({170.f, 150.f});
        this->gameOverText1.setString(ss1.str());

        stringstream ss2;
        ss2 << "  Continue       "
           << "      Quit";
        this->gameOverText2.setPosition(this->continueButton.getPosition());
        this->gameOverText2.setString(ss2.str());
    }
    else {
        stringstream ss;
        ss << "Keys : " << this->points << "/2"
           << "            PM : " << this->playerMovementLeft
           << "            PA : " << this->actionsLeft;
        this->ongoingText.setPosition({15.f, 5.f});
        this->ongoingText.setString(ss.str());
    }
}

void Engine::resetGame() {
    /*
     *@return void
     *
     * Resets the board to the original state.
     * -Delete the remaining keys
     * -Spawn all entities again
     * -Close all the doors
     * -Reset all necessary variables
     */
    // Delete remaining keys
    for (int i = 0; i < this->keys.size(); i++){
        this->keys.erase(this->keys.begin() + i);
        this->visibleKeys.erase(this->visibleKeys.begin() + i);
    }

    // Parameters
    this->myTurn = true;
    this->pullingLever = false;
    this->playerMovementLeft = playerMovement;
    this->actionsLeft = actions;
    this->enemyMovementLeft = enemyMovement;
    this->points = 0;
    this->forbiddenTiles = {this->startingPosition, this->exit.getPosition()};

    // Objects
    this->spawnEntities();
    this->resetDoors();

    // Sprites
    this->player.setTexture(this->playerTextureFront);
    this->enemy.setTexture(this->minotaurTextureFront);
    this->key.setTexture(this->keyTexture);

}

void Engine::updateGameOverScreen() {
    /*
     *@return void
     *
     * Manage the game over screen buttons
     * -Continue to reset the game
     * -Quit to close the window
     */

    if (Mouse::isButtonPressed(Mouse::Left)) {
        if (this->continueButton.getGlobalBounds().contains(this->mousePosView)) {
            this->resetGame();
            this->gameOver = false;
        }
        else if (this->quitButton.getGlobalBounds().contains(this->mousePosView)) {
            this->window->close();
        }
    }
}

void Engine::update() {
    /*
     *@return void
     *
     * Executes all the "update" functions.
     * -If the minotaur catches the player, game over
     * -If the player reaches the exit tile, you win
     */

    if (gameOver) {
        while (this->window->pollEvent(this->event)) {
            this->updateWindow();
            this->updateMousePosition();
            this->updateGameOverScreen();
        }
    } else {
        while (this->window->pollEvent(this->event)) {
            this->updateWindow();
            if (this->myTurn){
                this->updatePlayer();
            }
        }

        if (!this->myTurn){
            this->updateEnemies();
        }

        this->updateTurns();
        this->updateKeys();

        if (this->player.getPosition()==this->enemy.getPosition()) {
            this->gameOver = true;
            this->victory = false;
        } else if (this->player.getPosition()==this->exit.getPosition() && this->points==2) {
            this->gameOver = true;
            this->victory = true;
        }
    }
    this->updateText();
}
