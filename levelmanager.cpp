#include "levelmanager.h"

LevelManager::LevelManager():
    playerInfo(new PlayerInfo(1, 112, 100, 100, 0, 0)),
    gui(new GameWindow(nullptr))
{
    for (int level = MAX_LEVEL; level >= 1; level--)
    {
        // Construct all levels at the beginning, and store into the nextLevel stack
        currentLevel = new GameInstance(level, gui);
        nextLevel.push(currentLevel);
        connect(currentLevel, &GameInstance::goUpStairs, this, &LevelManager::levelDown);
        connect(currentLevel, &GameInstance::goDownStairs, this, &LevelManager::levelUp);
    }
    // Take the 1st level out from the stack of nextLevel
    currentLevel = nextLevel.top();
    gui->setGame(currentLevel);
    nextLevel.pop();
}

LevelManager::~LevelManager()
{
    if (currentLevel != nullptr)
        delete currentLevel;
    while (nextLevel.size() != 0)
    {
        currentLevel = nextLevel.top();
        nextLevel.pop();
        delete currentLevel;
    }
    while (previousLevel.size() != 0)
    {
        currentLevel = previousLevel.top();
        previousLevel.pop();
        delete currentLevel;
    }

    currentLevel = nullptr;
    delete gui;
    gui = nullptr;
}

int LevelManager::getMaxLevel() const { return MAX_LEVEL; }

GameInstance* LevelManager::getCurrentLevel() const { return currentLevel; }

PlayerInfo* LevelManager::getPlayerInfo() const { return playerInfo; }

void LevelManager::levelUp()
{
    if (nextLevel.size() != 0)
    {
        // Update the player information with respect to the current level
        playerInfo->setRowatLevel(currentLevel->getMapLevel() - 1, currentLevel->getPlayer()->getRow());
        playerInfo->setColatLevel(currentLevel->getMapLevel() - 1, currentLevel->getPlayer()->getCol());
        playerInfo->setLevel(currentLevel->getPlayer()->getLevel());
        playerInfo->setHealth(currentLevel->getPlayer()->getHealth());
        playerInfo->setAttack(currentLevel->getPlayer()->getAttack());
        playerInfo->setDefense(currentLevel->getPlayer()->getDefense());
        playerInfo->setNumOfKey(YELLOW, currentLevel->getPlayer()->getNumYellowKey());
        playerInfo->setNumOfKey(BLUE, currentLevel->getPlayer()->getNumBlueKey());

        // Update the coordinates of the next level with respect to the current level
        playerInfo->setRowatLevel(currentLevel->getMapLevel(), currentLevel->getPlayer()->getRow());
        playerInfo->setColatLevel(currentLevel->getMapLevel(), currentLevel->getPlayer()->getCol());

        // Push the current level into the previous levels stack
        // Get the next level to process
        // And update the player information and gui accordingly
        currentLevel->get_gui()->clearScreen();
        previousLevel.push(currentLevel);

        currentLevel = nextLevel.top();
        nextLevel.pop();

        gui->setGame(currentLevel);
        *(currentLevel->getPlayer()) = playerInfo;
        currentLevel->startGraphicUI();
    }
}

void LevelManager::levelDown()
{
    if (previousLevel.size() != 0)
    {
        // Update the player information with respect to the current level
        playerInfo->setRowatLevel(currentLevel->getMapLevel() - 1, currentLevel->getPlayer()->getRow());
        playerInfo->setColatLevel(currentLevel->getMapLevel() - 1, currentLevel->getPlayer()->getCol());
        playerInfo->setLevel(currentLevel->getPlayer()->getLevel());
        playerInfo->setHealth(currentLevel->getPlayer()->getHealth());
        playerInfo->setAttack(currentLevel->getPlayer()->getAttack());
        playerInfo->setDefense(currentLevel->getPlayer()->getDefense());
        playerInfo->setNumOfKey(YELLOW, currentLevel->getPlayer()->getNumYellowKey());
        playerInfo->setNumOfKey(BLUE, currentLevel->getPlayer()->getNumBlueKey());

        // Update the coordinates of the previous level with respect to the current level
        playerInfo->setRowatLevel(currentLevel->getMapLevel() - 2, currentLevel->getPlayer()->getRow());
        playerInfo->setColatLevel(currentLevel->getMapLevel() - 2, currentLevel->getPlayer()->getCol());

        // Push the current level into the next levels stack
        // Get the previous level to process
        // And update the player information and gui accordingly
        currentLevel->get_gui()->clearScreen();
        nextLevel.push(currentLevel);

        currentLevel = previousLevel.top();
        previousLevel.pop();

        gui->setGame(currentLevel);
        *(currentLevel->getPlayer()) = playerInfo;
        currentLevel->startGraphicUI();
    }
}
