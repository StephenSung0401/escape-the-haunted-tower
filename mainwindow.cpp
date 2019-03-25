#include <QFont>
#include <QFontDatabase>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gameinstance.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    levelManager(nullptr)
{
    ui->setupUi(this);

    connect(this->ui->startButton, &QPushButton::clicked, this, &MainWindow::startButton_clicked_handler);
}

MainWindow::~MainWindow()
{
    delete this->ui;
    delete levelManager;
}

void MainWindow::startButton_clicked_handler()
{
    if (this->levelManager) delete this->levelManager;
    this->levelManager = new LevelManager();
    this->levelManager->getCurrentLevel()->startGraphicUI();
    connect(this->levelManager->getCurrentLevel()->get_gui(), &GameWindow::closed, this, &MainWindow::game_window_closed_handler);
    this->hide();
}

void MainWindow::game_window_closed_handler() {
    this->show();
}

