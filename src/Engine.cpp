#include "Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60);

void Engine::initConstants() {
    /*
     * @return void
     *
     * Initialize the different constants
     */
    this->playerMovement = 2;
    this->actions = 2;
    this->enemyMovement = 2;
    this->numberKeys = 2;
    this->startingPosition = {80.f , 80.f};
}

void Engine::initVariables() {
    /*
     * @return void
     *
     * Initialize the different variables
     */

    this->window = nullptr;

    // Game logic
    this->myTurn = true;
    this->pullingLever = false;
    this->playerMovementLeft = playerMovement;
    this->actionsLeft = actions;
    this->enemyMovementLeft = enemyMovement;
    this->forbiddenTiles = {this->startingPosition, this->exit.getPosition()};
    this->points = 0;
    this->gameOver = false;
    this->victory = false;

    // Game objects
    this->exit.setPosition(280.f, 280.f);
    this->helper.setPosition(280.f, 280.f);
}

void Engine::initWindow() {
    /*
     * @return void
     *
     * Initialize the window in which we display everything
     */

    this->videoMode.height = 600;
    this->videoMode.width = 600;
    this->window = new RenderWindow(this->videoMode, "Game1");
    this->window->setFramerateLimit(FPS);
}

void Engine::initText() {
    /*
     * @return void
     *
     * Initialize the text for ongoing game and game over screen
     */
    this->font.loadFromFile("fonts\\Dosis-Light.ttf");
    this->ongoingText.setFont(this->font);
    this->ongoingText.setCharacterSize(42);
    this->ongoingText.setFillColor( Color::White);
    this->ongoingText.setString("None");

    this->gameOverText1.setFont(this->font);
    this->gameOverText1.setCharacterSize(42);
    this->gameOverText1.setFillColor(Color::White);
    this->gameOverText1.setString("None");

    this->gameOverText2.setFont(this->font);
    this->gameOverText2.setCharacterSize(42);
    this->gameOverText2.setFillColor(Color::Black);
    this->gameOverText2.setString("None");

}

void Engine::initObjects() {
    /*
     * @return void
     *
     * Initialize the different objects
     * -The player
     * -The enemy (minotaur)
     * -The keys
     * -The exit ladder
     */
    this->playerTextureFront.loadFromFile("sprite\\player_front.jpg");
    this->playerTextureLeft.loadFromFile("sprite\\player_left.jpg");
    this->playerTextureRight.loadFromFile("sprite\\player_right.jpg");
    this->playerTextureBack.loadFromFile("sprite\\player_back.jpg");
    // Sprite size 65 x 65 pixels
    this->player.setTexture(this->playerTextureFront);

    this->minotaurTextureFront.loadFromFile("sprite\\minotaur_front.jpg");
    this->minotaurTextureLeft.loadFromFile("sprite\\minotaur_left.jpg");
    this->minotaurTextureRight.loadFromFile("sprite\\minotaur_right.jpg");
    this->minotaurTextureBack.loadFromFile("sprite\\minotaur_back.jpg");
    //
    this->enemy.setTexture(this->minotaurTextureFront);

    this->keyTexture.loadFromFile("sprite\\key.jpg");
    this->key.setTexture(this->keyTexture);

    this->exitTexture.loadFromFile("sprite\\ladder.jpg");
    this->exit.setTexture(this->exitTexture);
}

void Engine::initBackground() {
    /*
     * @return void
     *
     * Initialize the background
     * -The floor tiles
     * -The doors
     */

    // initialize the background tiles
    this->tile.setSize(Vector2f(95.f, 95.f));
    this->tile.setFillColor(Color::White);


    // initialize the vertical doors
    for (int i = 0; i < 4; ++i) {
        vector<RectangleShape> v;
        vector<bool> isV;
        for (int j = 0; j < 5; ++j) {
            // Rendering vertical doors
            if (i==0 && j==0) {
                this->verticalDoor.setFillColor(Color::Green);
                this->verticalDoor.setSize(Vector2f(10.f, 60.f));
                this->verticalDoor.setPosition(Vector2f(
                        160.f,
                        82.f
                ));
                v.push_back(this->verticalDoor);
                isV.push_back(true);
            } else {
                this->verticalDoor.setFillColor(Color::Red);
                this->verticalDoor.setSize(Vector2f(10.f, 60.f));
                this->verticalDoor.setPosition(Vector2f(
                        static_cast<float> (100*i+160),
                        static_cast<float> (100*j+82)
                ));
                v.push_back(this->verticalDoor);
                isV.push_back(false);
            }
        }
        this->vDoors.push_back(v);
        this->isVDoorOpen.push_back(isV);
    }

    // initialize the horizontal doors
    for (int i = 0; i < 5; ++i) {
        vector<RectangleShape> h;
        vector<bool> isH;
        for (int j = 0; j < 4; ++j) {
            // Rendering horizontal doors
            if (i==0 && j==0) {
                // First door is always opened (and invisible, only for practicality)
                this->horizontalDoor.setFillColor(Color::Green);
                this->horizontalDoor.setSize(Vector2f(60.f, 10.f));
                this->horizontalDoor.setPosition(Vector2f(
                        82.f,
                        160.f
                ));
                h.push_back(this->horizontalDoor);
                isH.push_back(true);
            } else {
                this->horizontalDoor.setFillColor(Color::Red);
                this->horizontalDoor.setSize(Vector2f(60.f, 10.f));
                this->horizontalDoor.setPosition(Vector2f(
                        static_cast<float> (100*i+82),
                        static_cast<float> (100*j+160)
                ));
                h.push_back(this->horizontalDoor);
                isH.push_back(false);
            }
        }
        this->hDoors.push_back(h);
        this->isHDoorOpen.push_back(isH);
    }

    // Prepare the game over screen
    this->endScreen.setPosition(0.f, 0.f);
    this->endScreen.setFillColor(Color::Black);
    this->endScreen.setSize({600.f, 600.f});
    this->continueButton.setPosition(115.f, 250.f);
    this->continueButton.setSize({180.f, 50.f});
    this->continueButton.setFillColor(Color::Green);
    this->continueButton.setOutlineThickness(2.f);
    this->continueButton.setOutlineColor(Color::White);
    this->quitButton.setPosition(315.f, 250.f);
    this->quitButton.setSize({180.f, 50.f});
    this->quitButton.setFillColor(Color::Red);
    this->quitButton.setOutlineThickness(2.f);
    this->quitButton.setOutlineColor(Color::White);

}

//Constructors / Destructors
Engine::Engine() {
    this->initConstants();
    this->initVariables();
    this->initWindow();
    this->initText();
    this->initObjects();
    this->initBackground();
}

Engine::~Engine() {
    delete this->window;
}

// Accessors
bool Engine::getWindowIsOpen() const {
    return this->window->isOpen();
}

void Engine::run() {
    // Main Loop, run until the window is closed
    update();
    draw();
}
