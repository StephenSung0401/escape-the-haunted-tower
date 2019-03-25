#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include <QObject>
#include "gamewindow.h"
#include "Block/block.h"
#include "Block/monster.h"
#include "items/Item.h"
#include "player/Player.h"
#include <QKeyEvent>
#include <iostream>

/* The class that is constructed based on the level's txt map data. This controls the general flow of the game.
 * Controls the GUI while controlling the gameflow to interact with the screen.
 * Has layers of data about the map blocks, monsters, and items.
 * It also constructs the player based on the player information passed from previous level, so that player can freely switch level (floor)
 * without losing its data.
 * ***do not mistake level and MapLevel;  (above mentioned "level" is basically MapLevel)
 * level = player's level, which is increased when player goes down one floor. Increases player's ability.
 * MapLevel = the floor in the Haunted House.
*/

class GameWindow;

class GameInstance: public QObject {
    Q_OBJECT
    friend GameWindow;
public:
    GameInstance(int level, GameWindow* gui);
    ~GameInstance();

    int getMapLevel() const;
    GameWindow* get_gui() const;
    Player* getPlayer() const;
    void startGraphicUI();
    void move(int, int);
    void collect(int, int);
    void open(int, int);
    void kill(int, int);
    void useStair(int, int);
    void gameWin();

private:
    int mapLevel;
    GameWindow* gui;
    Block* map[9][9] = {{nullptr}};
    Monster* monster[9][9] = {{nullptr}};
    Item* item[9][9] = {{nullptr}};
    Player* player = nullptr;
    bool GameOver = false;

    void makeMap(int);

private slots:
    void processUserInput(int row, int col);

signals:
    void goUpStairs();
    void goDownStairs();

};

#endif // GAMEINSTANCE_H
