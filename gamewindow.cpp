#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "gameinstance.h"
#include "Block/door.h"

#include <QDebug>

using std::string;



GameWindow::GameWindow(GameInstance* _game, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    monsterInfo(nullptr),
    attack(nullptr),
    game(_game),
    monster_row(-1),
    monster_col(-1),
    timer(new QTimer(this)),
    attack_timer (new QTimer(this))
{
    ui->setupUi(this);

    //hide monsterInfo stuff
    ui->MAL->hide();
    ui->MDL->hide();
    ui->MHL->hide();
    ui->monster_HP->hide();
    ui->monster_AP->hide();
    ui->monster_DP->hide();

    //hide gameover stuff
    ui->progressBar->hide();
    ui->GameOver->hide();
    ui->gameover_player->hide();
    ui->Level1->hide();
    ui->Level2->hide();
    ui->Level3->hide();
    ui->desmond->hide();
    ui->desmond_fail_message->hide();
    ui->desmond_successful_message->hide();

    //the timer for gameover animation and attack animation
    timer->setInterval(1000);
    attack_timer->setInterval(150);
    attack_timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &GameWindow::GameOverAnimation);
    connect(attack_timer, &QTimer::timeout, this, &GameWindow::AttackAnimation);
}

GameWindow::~GameWindow() {
    delete ui;
    delete timer;
    delete attack_timer;
}

void GameWindow::setGame(GameInstance* _game)
{
    game = _game;
}

void GameWindow::closeEvent(QCloseEvent *event) {
    emit closed();
}

void GameWindow::showMap() {
    for (int row = 0; row < 9; ++row){
        for (int col = 0; col < 9; ++col){

            if (game->monster[row][col] != nullptr){

                monsterIcon[row][col] = new MonsterIcon(row, col, game->monster[row][col]->getImage(), this);
                game->monster[row][col]->raise();
                game->monster[row][col]->show();
                connect(game->monster[row][col], &Monster::clicked_with_pos, this, &GameWindow::updateMonsterInfo);
            }

            if (game->item[row][col] != nullptr){
                game->item[row][col]->setPixmap(game->item[row][col]->getImage());
                game->item[row][col]->show();
            }

            if (game->map[row][col] != nullptr){
                game->map[row][col]->setPixmap(game->map[row][col]->getImage());
                game->map[row][col]->show();
            }
        }
    }
}

void GameWindow::updateMonsterInfo(int row, int col)
{
    if (game->GameOver) return;
    if (monster_row == row && monster_col == col) return;

    if (monsterInfo != nullptr){
        delete monsterInfo;
        monsterInfo = nullptr;
    }

    monster_row = row; monster_col = col;

    QString HP = QString::number(game->monster[row][col]->getHP());
    QString attack = QString::number(game->monster[row][col]->getAttack());
    QString Defense = QString::number(game->monster[row][col]->getDefense());

    ui->MAL->show();
    ui->MDL->show();
    ui->MHL->show();
    ui->monster_HP->setText(HP); ui->monster_HP->show();
    ui->monster_AP->setText(attack); ui->monster_AP->show();
    ui->monster_DP->setText(Defense); ui->monster_DP->show();

    monsterInfo = new MonsterIcon(3,11, game->monster[row][col]->getImage(), this);
    monsterInfo->move(790,330);

}

void GameWindow::updateScreen() // to handle player's movement. Other things are done almost automatically
{
    if (game->monster[monster_row][monster_col] == nullptr)
        resetMonsterInfo();

    //don't show the monster if killed
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j <9; ++j){
            if (game->monster[i][j] == nullptr && monsterIcon[i][j] != nullptr){
                delete monsterIcon[i][j];
                monsterIcon[i][j] = nullptr;
            }
        }
    }

    //move player
    game->player->setPixmap(game->player->getImage());
    game->player->setGeometry(QRect(0 + 70 * game->player->getCol(), 70 + 70 * (7-game->player->getRow()), 70, 70));
    game->player->show();
    updatePlayerInfo();
}

void GameWindow::updatePlayerInfo()
{
    QString level = QString:: number(4 - game->player->getMapLevel());
    QString Health = QString:: number(game->player->getHealth());
    QString attack = QString:: number(game->player->getAttack());
    QString defense = QString:: number(game->player->getDefense());
    QString YK = QString:: number(game->player->getNumYellowKey());
    QString BK = QString:: number(game->player->getNumBlueKey());

    ui->player_level->setText(level);
    ui->player_HP->setText(Health);
    ui->player_AP->setText(attack);
    ui->player_DP->setText(defense);
    ui->player_YK->setText(YK);
    ui->player_BK->setText(BK);

}

void GameWindow::resetMonsterInfo()
{
    ui->MAL->hide();
    ui->MDL->hide();
    ui->MHL->hide();
    ui->monster_HP->hide();
    ui->monster_AP->hide();
    ui->monster_DP->hide();
    if (monsterInfo != nullptr){
        delete monsterInfo;
        monsterInfo = nullptr;
    }
}

//handle the keypress (up, down, left, right)
//support both arrow keys as well as WASD and HJKL (vim)
void GameWindow::keyPressEvent(QKeyEvent *event){
    int row = game->player->getRow();
    int col = game->player->getCol();
    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_W || event->key() == Qt::Key_K){
        game->player->setOrientation(Up);
        game->processUserInput(row + 1, col);
    }
    else if(event->key() == Qt::Key_Down || event->key() == Qt::Key_S || event->key() == Qt::Key_J){
        game->player->setOrientation(Down);
        game->processUserInput(row - 1, col);
    }
    else if(event->key() == Qt::Key_Left || event->key() == Qt::Key_A || event->key() == Qt::Key_H){
        game->player->setOrientation(Left);
        game->processUserInput(row, col - 1);
    }
    else if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D || event->key() == Qt::Key_L){
        game->player->setOrientation(Right);
        game->processUserInput(row, col + 1);
    }
}

void GameWindow::clearScreen()
{
    resetMonsterInfo();
    game->player->hide();
    for (int i = 0; i < 9; ++i){
        for (int j =0; j <9; ++j){
            if (monsterIcon[i][j] != nullptr){
                delete monsterIcon[i][j];
                monsterIcon[i][j] = nullptr;
            }
            if (game->item[i][j] != nullptr){
                game->item[i][j]->hide();
            }
            if (game->map[i][j] != nullptr){
                game->map[i][j]->hide();
            }
        }
    }
}

void GameWindow::showGameOverScreen(){
    clearScreen();
    ui->progressBar->show();
    ui->GameOver->show();
    ui->gameover_player->move(160,370);
    ui->gameover_player->show();
    timer->start();
}

void GameWindow::GameOverAnimation(){

    if (num_levels == 4){
        ui->GameOver->setText("Congratulations!");

        if (!savedDesmond){
            ui->desmond->show();
            ui->desmond_fail_message->show();
            timer->stop();
            return;
        }
        else{
            ui->desmond->show();
            ui->desmond_successful_message->show();
            timer->stop();
            return;
        }
    }

    ui->gameover_player->move(160+num_levels*175,370);
    ui->progressBar->setValue(num_levels*33);
    switch(num_levels){
    case 1:
        ui->Level1->show();
        break;
    case 2:
        ui->Level2->show();
        break;
    case 3:
        ui->Level3->show();
        break;
    }
    num_levels++;
}


void GameWindow::setDesmond(bool saved) {savedDesmond = saved;}

void GameWindow::startAttack(int row, int col)
{

    if (attack != nullptr)
        delete attack;


    attack = new MonsterIcon(row, col, ":/images/attack.png", this);

    attack_timer->start();
}


void GameWindow::AttackAnimation()
{
    delete attack;
    attack = nullptr;

    attack_timer->stop();
}





