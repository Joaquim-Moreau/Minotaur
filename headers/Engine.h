#ifndef MINOTAUR_ENGINE_H
#define MINOTAUR_ENGINE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <ctime>
#include <sstream>

using namespace sf;
using namespace std;

class Engine {
private:
    // Window
    Event event{};
    RenderWindow* window;
    VideoMode videoMode;

    // Texture
    Texture playerTextureFront;
    Texture playerTextureLeft;
    Texture playerTextureRight;
    Texture playerTextureBack;

    Texture minotaurTextureFront;
    Texture minotaurTextureLeft;
    Texture minotaurTextureRight;
    Texture minotaurTextureBack;

    Texture keyTexture;
    Texture exitTexture;

    // Text
    Font font;
    Text gameOverText1;
    Text gameOverText2;
    Text ongoingText;

    // Mouse position
    Vector2i mousePosWindow;
    Vector2f mousePosView;

    // Variables
    // Game logic
    bool myTurn;
    bool pullingLever;

    int playerMovement;
    int playerMovementLeft;

    int actions;
    int actionsLeft;

    int enemyMovement;
    int enemyMovementLeft;

    Vector2f startingPosition;

    const unsigned int FPS = 10;
    static const Time TimePerFrame;

    int numberKeys;
    vector<bool> visibleKeys;
    vector<Vector2f> forbiddenTiles;
    int points;
    bool gameOver;
    bool victory;

    // Game objects
    // Entities
    Sprite player;
    Sprite enemy;
    Sprite helper;

    // Keys
    Sprite key;
    vector<Sprite> keys;

    // Background
    Sprite exit;
    RectangleShape tile;

    // Doors
    vector<vector<RectangleShape>> vDoors;
    vector<vector<bool>> isVDoorOpen;
    RectangleShape verticalDoor;
    vector<vector<RectangleShape>> hDoors;
    vector<vector<bool>> isHDoorOpen;
    RectangleShape horizontalDoor;

    // Game over screen
    RectangleShape endScreen;
    RectangleShape continueButton;
    RectangleShape quitButton;


    // Private Functions
    void initVariables();
    void initConstants();
    void initWindow();
    void initText();
    void initObjects();
    void initBackground();
public:
    // Constructors / Destructors
    Engine();
    virtual ~Engine();

    // Accessors
    bool getWindowIsOpen() const;

    // Functions
    // Spawn everything
    void spawnPlayer();
    void spawnEnemy();
    void spawnKeys();
    void resetDoors();
    void spawnEntities();

    // Update the board after each action/movement
    void updateWindow();
    void updateTurns();
    void updateMousePosition();
    void updatePlayer();
    void updateEnemies();
    void openDoor(Vector2i doorID, const string & orientation);
    void closeDoor(Vector2i doorID, const string & orientation);
    static void moveEntity(Sprite &entity, const string & direction);
    void changeDoorColor(Vector2i doorID, const string & orientation, Color color);
    void pullLever(Sprite &entity, const string & direction);
    void updateKeys();
    void updateText();
    void resetGame();
    void updateGameOverScreen();
    void update();

    // Draw the board
    void draw();
    void drawPlayer();
    void drawBackground();
    void drawEnemies();
    void drawText();
    void drawKeys();
    void drawGameOver();

    // Useful functions
    static bool isMovePossible(const Sprite &entity, const string & direction);
    bool isDoorOpen(const Sprite &entity, const string & direction);
    bool isThereADoor(const Sprite &entity, const string & direction);
    Vector2i getDoorID(const Sprite &entity, const string & direction);
    bool isForbidden(Vector2f position);
    static Vector2f getRandomTile();
    Vector2f convertPosition(const Sprite &entity);
    bool comparePosition(const Sprite &entity1, const Sprite &entity2);
    bool isAligned(const Sprite &entity1, const Sprite &entity2);

    // The main loop will be in the run function
    void run();
};

#endif //MINOTAUR_ENGINE_H
