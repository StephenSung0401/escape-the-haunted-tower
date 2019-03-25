#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "levelmanager.h"
#include "gamewindow.h"

/* this class handles the main window: the starting window when the game is first opened.
 * It is actually out of the game, so holds the data that should be dealt outside each level,
 * i.e. the gui (we are using only one game window for all levels), or the player info. (these two are done in level manager, and main window owns the level manager)
*/
namespace Ui {
class MainWindow;
}

class GameInstance;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Player* getPlayer() const; //returns the player, needed in the level manager, since we have to update the playerInfo accordingly when we change level.

private:
    Ui::MainWindow *ui; //to access the members created through ui editor; although we did not use it, it is left here so that further improvement may be done.
    LevelManager* levelManager; //points to the level manager object which creates the game instances for the 3 levels.

private slots:
    void startButton_clicked_handler(); //handle the game start when the button is clicked. Calls the level manager to create levels, and start the gui. Also, hide main window while playing game.
    void game_window_closed_handler(); //Show main window again when game window closed.
};

#endif // MAINWINDOW_H
