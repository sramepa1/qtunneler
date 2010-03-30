/*
 * File:   GameWindow.cpp
 * Author: pavel
 *
 * Created on 19. březen 2010, 12:27
 */

#include "GameWindow.h"

GameWindow::GameWindow() {

    setWindowTitle("QTunneler");

    actionCreateJoin = new QAction("Create/Join",this);
    actionExit = new QAction("Exit",this);
    
    menuGame = new QMenu("Game");
    menuBar = new QMenuBar;
    
    drawArea = new QWidget();
    
    statusBar = new QStatusBar;

    menuGame->addAction(actionCreateJoin);
    menuGame->addAction(actionExit);
    menuBar->addMenu(menuGame);

    setMenuBar(menuBar);
    setCentralWidget(drawArea);
    setStatusBar(statusBar);

    statusBar->showMessage("Initializing game. Please wait...");

    setMinimumSize(640,480);

    resize(1024,768);

    connect(actionCreateJoin,SIGNAL(triggered()),this,SLOT(hideWindowAndSwitch()));
    connect(actionExit,SIGNAL(triggered()),this,SLOT(exit()));

}

void GameWindow::hideWindowAndSwitch() {
    hide();
    emit switchToDialog();
}

void GameWindow::showWindow() {
    show();
}

void GameWindow::exit() {
    close();
    // TODO
}
