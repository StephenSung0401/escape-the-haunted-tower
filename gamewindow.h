#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QFont>
#include <QTimer>

#include "monstericon.h"

/* The GUI of the game. One window is used for all levels, so we clear it, and re-use it.
 * just deals with the showing of image and stuff, and the game flow is controlled in game instance.
 * so the game instance calls the function of the Game Window to update the screen accirdingly.
 * Also, this is the friend class of the game instance for efficiency,
 * since it has to access the data members and mutate them very frequently.
*/

//all the images used are referenced in the :/images/sources/image_references.txt

namespace Ui {
class GameWindow;
}

class GameInstance;

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(GameInstance* _game=nullptr, QWidget *parent = nullptr);
    ~GameWindow();

    void showMap(); //to be called in gameinstance's startGUI(), shows the image according to the map data in GameInstance
    void updateScreen(); //to be called in processUserInput, so when there is a user input, it should be called. Also, when the GUI starts, also should be called.
    void resetMonsterInfo(); //clear monsterInfo screen, called if the monster is killed
    void updatePlayerInfo(); //updates information of player, HP, attack, defense, etc. called in updateScreen, since they should be called at the same time to keep the user updated of the data.
    void setGame(GameInstance* game); //since we use only one GameWindow for 3 GameInstances of each level, the GameWindow should be informed which GameInstance it is pointing right now when the level changes.
    void setDesmond(bool saved); //when the desmond is saved, set it true.

    // Keypress detection
    void keyPressEvent(QKeyEvent *event); //handles the key press events, and calls GameInstance's process user input to control game flow.

    void clearScreen(); //clears screen when needed: change level, or game over.
    void showGameOverScreen(); //shows the game over screen and starts the timer for animation to start.
    void startAttack(int row, int col);

private:
    void closeEvent(QCloseEvent *event);

    Ui::GameWindow *ui; //to access the data members added through ui editor.

    MonsterIcon* monsterIcon[9][9] = {{nullptr}}; //icon for monster: constructed based on game instance's monster array, and this is imposed below the monster so that it shows the image, yet the monster, (which is left transparent) can still be clicked.
    MonsterIcon* monsterInfo; //The monster Icon to be shown in the monster information screen when the monster is clicked.
    MonsterIcon* attack;

    GameInstance* game; //the current game instance. i.e. the current game level.
    int monster_row, monster_col; //to store the currently clicked monster's row and coloumn.
    QTimer* timer; // to be used in game over animation.
    QTimer* attack_timer;
    int num_levels = 1; //used to control how many times timer is called.
    bool savedDesmond = false; //if the user saves Desmond, it is set to true.

private slots:
    void updateMonsterInfo(int row, int col); //connected to clicked with pos of game instance, and shows the information of the clicked monster in the monster information section.
    void AttackAnimation();
    void GameOverAnimation(); //need to show the animation by iteration, so connected to timer.

signals:
    void closed();
};

#endif // GAMEWINDOW_H
