#include "Engine.h"

void Engine::drawPlayer() {
    /*
        @return void

        Renders the player
     */

    this->window->draw(this->player);
}

void Engine::drawBackground() {
    /*
        @return void

        Renders the background tiles and the doors
     */

    // Rendering the doors
    for (int i = 0; i < this->vDoors.size(); ++i) {
        for (int j = 0; j < this->vDoors[i].size(); ++j) {
            if (!(i==0 && j==0)) {
                this->window->draw(this->vDoors[i][j]);
            }
        }
    }

    for (int i = 0; i < hDoors.size(); ++i) {
        for (int j = 0; j < hDoors[i].size(); ++j) {
            if (!(i==0 && j==0)) {
                this->window->draw(hDoors[i][j]);
            }
        }
    }

    // Rendering the floor tiles
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            this->tile.setPosition(Vector2f(
                    static_cast<float> (100*i+65),
                    static_cast<float> (100*j+65)
                    ));
            this->window->draw(this->tile);
        }
    }

    // Rendering the exit
    this->window->draw(this->exit);
}

void Engine::drawEnemies() {
    /*
        @return void

        Renders the enemy
     */

    this->window->draw(this->enemy);
}

void Engine::drawKeys() {
    /*
        @return void

        Renders the keys
     */

    for (int i = 0; i < this->keys.size(); ++i) {
        //if (this->visibleKeys[i]) {
        //    this->window->draw(this->keys[i]);
        //}
        this->window->draw(this->keys[i]);
    }
}

void Engine::drawText() {
    /*
        @return void

        Renders the text
     */
    if (gameOver) {
        this->window->draw(this->gameOverText1);
        this->window->draw(this->gameOverText2);
    }
    else {
        this->window->draw(this->ongoingText);
    }

}

void Engine::drawGameOver() {
    /*
        @return void

        Renders the button on game over text
     */
    this->window->draw(this->endScreen);
    this->window->draw(this->continueButton);
    this->window->draw(this->quitButton);
}

void Engine::draw() {
    /*
        @return void

        -clear old frame
        -draw the different objects
        -display new frame

        Renders the game objects
     */

    this->window->clear();

    // Draw
    if (gameOver){
        this->drawGameOver();
    } else {
        this->drawBackground();
        this->drawPlayer();

        this->drawKeys();
        this->drawEnemies();
    }

    this->drawText();
    this->window->display();
}




