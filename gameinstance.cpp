#include "gameinstance.h"
#include "player/Player.h"
#include "Block/wall.h"
#include "Block/door.h"
#include "Block/monster_a.h"
#include "Block/monster_b.h"
#include "Block/monster_c.h"
#include "items/Diamond.h"
#include "items/Key.h"
#include "items/Potion.h"
#include "player/PlayerInfo.h"
#include "Block/stair.h"
#include "Block/exit.h"
#include "items/Desmond.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>
#include <QIcon>

GameInstance::GameInstance(int _level, GameWindow* _gui):
mapLevel{_level},
gui{_gui},
player{new Player(gui, mapLevel, 1, 1)}
{
     makeMap(mapLevel);
}

GameInstance::~GameInstance(){
    if (player != nullptr) delete player;
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            if (map[i][j]!=nullptr) delete map[i][j];
            if (monster[i][j]!=nullptr) delete monster[i][j];
            if (item[i][j]!=nullptr) delete item[i][j];
        }
    }

}

int GameInstance::getMapLevel() const { return mapLevel; }

GameWindow* GameInstance::get_gui() const
{
    return gui;
}

Player* GameInstance::getPlayer() const { return player; }

void GameInstance::startGraphicUI()
{
    player->setPixmap(player->getImage());
    gui->show();
    gui->showMap();
    gui->updateScreen();
}

//initialize the map
void GameInstance::makeMap(int _level) {

    QString dir = ":levels/level" + QString::number(_level) + ".txt";

    QFile map(dir);

    map.open(QIODevice:: ReadOnly);
    QTextStream input(&map);

    QString line = input.readLine();
    for (int row =0; row<9;++row){
        line.remove(" ");
        line.remove("\n");
        for (int col = 0; col<9; col++){
            switch(line.at(col).toLatin1()){
            case '1':
                this->map[row][col] = new Wall(row, col, gui);
                break;
            case '2':
                this->map[row][col] = new Door(Color::YELLOW, row, col, gui);
                break;
            case '3':
                this->map[row][col] = new Door(Color::BLUE, row, col, gui);
                break;
            case '4':
                this->monster[row][col] = new MonsterA(row, col, gui);
                break;
            case '5':
                this->monster[row][col] = new MonsterB(row, col, gui);
                break;
            case '6':
                this->monster[row][col] = new MonsterC(row, col, gui);
                break;
            case '7':
                this->map[row][col] = new Stair(StairDirection::UPSTAIR, row, col, gui);
                break;
            case '8':
                this->map[row][col] = new Stair(StairDirection::DOWNSTAIR, row, col, gui);
                break;
            case '9':
                this->map[row][col] = new Exit(row, col, gui);
                break;
            case 'a':
                this->item[row][col] = new Diamond(gui, row, col, 'A');
                break;
            case 'd':
                this->item[row][col] = new Diamond(gui, row, col, 'D');
                break;
            case 'b':
                this->item[row][col] = new Key(gui, row, col, BLUE);
                break;
            case 'y':
                this->item[row][col] = new Key(gui, row, col, YELLOW);
                break;
            case 'l':
                this->item[row][col] = new Potion(gui, row, col, 'L');
                break;
            case 's':
                this->item[row][col] = new Potion(gui, row, col, 'S');
                break;
            case 't':
                this->item[row][col] = new Desmond(gui, row, col);
            }
        }
        line = input.readLine();
    }
    map.close();
}

//tell which operation should be made according to the nature of the square the player is trying to move to
void GameInstance::processUserInput(int row, int col)
{
    if (GameOver) return;

    //range check
    if(row < 0 || row > 8 || col < 0 || col > 8){
        return;
    }

    //square to go is empty
    else if(map[row][col] == nullptr && monster[row][col] == nullptr && item[row][col] == nullptr){
        move(row, col);
    }

    //square to go is block
    else if(map[row][col] != nullptr){
        //it is a wall, so the player cannot go there
        if(map[row][col]->getImage() == ":/images/wall.png"){
            gui->updateScreen();
            return;
        }
        //it is a door, the player needs key of cooresponding color to open it
        else if(map[row][col]->getImage() == ":/images/door-yellow.png" || map[row][col]->getImage() == ":/images/door-blue.png"){
            open(row, col);
        }
        //it is a stair, the player can travel to upper stairs or lower stairs
        else if(map[row][col]->getImage() == ":/images/stair-upright.png" || map[row][col]->getImage() == ":/images/stair-downleft.png"){
            useStair(row, col);
        }
        //it is the exit! the player will win and it will be the end of the game after the player reach
        else if(map[row][col]->getImage() == ":/images/exit.png"){
            gameWin();
            return;
        }
    }

    //square to go contain a monster, the player will try to fight with it
    else if(monster[row][col] != nullptr){
        kill(row, col);
    }

    //square to go contain an item, the player will collect it
    else if(item[row][col] != nullptr){
        collect(row, col);
    }

    //showing the message box when passing by Desmond if he is not yet saved
    if(player->getRow() == 3 && player->getCol() == 5 && item[3][7] != nullptr && item[3][7]->getImage() == ":/images/desmond.png"
            && map[3][6] != nullptr){
        gui->updateScreen();
        QPixmap iconPixmap(":/images/desmond.png");
        QMessageBox* Msgbox = new QMessageBox(QMessageBox::Critical, "Desmond needs your help", "I am trapped here! Please help me!", QMessageBox::Ok);
        Msgbox->setIconPixmap(iconPixmap);
        Msgbox->show();
        return;
    }
    gui->updateScreen();

}

//move the player
void GameInstance::move(int row, int col)
{

    if(row == player->getRow()){
        if(col == player->getCol() + 1){
            player->movement(Right);
            return;
        }
        else if(col == player->getCol() - 1){
            player->movement(Left);
            return;
        }
    }
    else if(col == player->getCol()){
        if(row == player->getRow() + 1){
            player->movement(Down);
            return;
        }
        else if(row == player->getRow() - 1){
            player->movement(Up);
            return;
        }
    }

}

//open the door
void GameInstance::open(int row, int col)
{
    if(map[row][col]->getImage() == ":/images/door-yellow.png"){
        if(player->getNumYellowKey() > 0){
            delete map[row][col];
            map[row][col] = nullptr;
            player->unlockDoor(YELLOW);
            return;
        }
    }
    else if(map[row][col]->getImage() == ":/images/door-blue.png"){
        if(player->getNumBlueKey() > 0){
            delete map[row][col];
            map[row][col] = nullptr;
            player->unlockDoor(BLUE);
            return;
        }
    }
}

//kill a monster
void GameInstance::kill(int row, int col)
{
    //player cannot hurt the monster at all, so nothing happen
    if(monster[row][col]->getDefense() >= player->getAttack()){
        emit monster[row][col]->clicked_with_pos(row, col);
        return;
    }
    //player can kill the monster without being hurted
    else if(player->getDefense() >= monster[row][col]->getAttack()){
        delete monster[row][col];
        gui->startAttack(row, col);
        monster[row][col] = nullptr;
    }
    //player will fight with the monster, attack each other alternatively,
    //with player attacks the monster first
    else{
        int monster_HP = monster[row][col]->getHP();
        int player_HP = player->getHealth();
        monster_HP -= player->getAttack() - monster[row][col]->getDefense();
        while(monster_HP > 0){
            player_HP -= monster[row][col]->getAttack() - player->getDefense();
            monster_HP -= player->getAttack() - monster[row][col]->getDefense();
        }
        //player is killed by the monster which is invalid in the game,
        //so we do nothing
        if(player_HP <= 0){
            emit monster[row][col]->clicked_with_pos(row, col);
            return;
        }
        //monster killed by the player
        else{
            player->health_change(player_HP - player->getHealth());
            gui->startAttack(row, col);
            delete monster[row][col];
            monster[row][col] = nullptr;
        }
    }
}

//collect an item
void GameInstance::collect(int row, int col)
{
    //it is a diamond which can boost the player's attack or defense
    if(item[row][col]->getImage() == ":/images/diamond-attack.png" || item[row][col]->getImage() == ":/images/diamond-defense.png"){
        Diamond* temp = static_cast<Diamond*>(item[row][col]);
        if(temp->getType() == 'A'){
            player->attack_change(temp->getValue());
            delete item[row][col];
            item[row][col] = nullptr;
            return;
        }
        else if(temp->getType() == 'D'){
            player->defense_change(temp->getValue());
            delete item[row][col];
            item[row][col] = nullptr;
            return;
        }
    }
    //it is a potion which can heal the player
    else if(item[row][col]->getImage() == ":/images/potion-blue.png" || item[row][col]->getImage() == ":/images/potion-red.png"){
        Potion* temp = static_cast<Potion*>(item[row][col]);
        player->health_change(temp->get_heal());
        delete item[row][col];
        item[row][col] = nullptr;
        return;
    }
    //it is a key
    else if(item[row][col]->getImage() == ":/images/key-yellow.png" || item[row][col]->getImage() == ":/images/key-blue.png"){
        Key* temp = static_cast<Key*>(item[row][col]);
        if(temp->getColor() == YELLOW){
            player->pickKey(YELLOW);
            delete item[row][col];
            item[row][col] = nullptr;
            return;
        }
        else if(temp->getColor() == BLUE){
            player->pickKey(BLUE);
            delete item[row][col];
            item[row][col] = nullptr;
            return;
        }
    }
    //Desmond is saved by the player
    else if(item[row][col]->getImage() == ":/images/desmond.png"){
        delete item[row][col];
        item[row][col] = nullptr;
        QPixmap iconPixmap(":/images/desmond.png");
        QMessageBox* Msgbox = new QMessageBox(QMessageBox::Critical, "Desmond Saved!", "Thank you! You are really a good guy! AAAAA!", QMessageBox::Ok);
        Msgbox->setIconPixmap(iconPixmap);
        Msgbox->show();
        gui->setDesmond(true);
        return;
    }
}

//go upstairs or downstairs, the player will upgrade and gain more HP, attack and defense for the first time it goes to the new floor
void GameInstance::useStair(int row, int col)
{
    if(map[row][col]->getImage() == ":/images/stair-upright.png"){
        emit goUpStairs();
    }
    else if(map[row][col]->getImage() == ":/images/stair-downleft.png"){
        if(mapLevel >= 3) return;
        else if(player->getLevel() < mapLevel + 1){
            player->upgrade();
        }
        emit goDownStairs();
    }
}

//showing the gameover screen
void GameInstance::gameWin(){
    GameOver = true;
    gui->showGameOverScreen();
}

