#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "gameinstance.h"
#include "player/player.h"
#include "player/playerinfo.h"
#include <stack>

using namespace std;

/*
    The Level manager controls and stores all the levels
    to enable the player to go to the next and PREVIOUS level
*/

class LevelManager: public QObject
{
public:
    LevelManager();
    ~LevelManager();

    int getMaxLevel() const;
    GameInstance* getCurrentLevel() const;
    PlayerInfo* getPlayerInfo() const;


private:
    static const int MAX_LEVEL = 3;

    GameInstance* currentLevel;     // GameInstance Pointer pointing at the current level
    stack<GameInstance*> nextLevel;      // A stack to store the upcoming levels (The larger level is at the bottom)
    stack<GameInstance*> previousLevel;  // A stack to store the passed levels (The smaller level is at the bottom)

    PlayerInfo* playerInfo;  // All the GameInstance shares the same player information storing in the PlayerInfo class
    GameWindow* gui;

private slots:
    // Level switching
    void levelUp();
    void levelDown();
};

#endif // LEVELMANAGER_H
