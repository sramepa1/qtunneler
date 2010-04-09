/*
 * File:   GameWindow.cpp
 * Author: pavel
 *
 * Created on 19. březen 2010, 12:27
 */

#include "GameWindow.h"
#include "DefaultValues.h"

GameWindow::GameWindow(Model* model) {

    setWindowTitle(APP_NAME_STRING);

    menuBar = new QMenuBar(this);
    menuGame = new QMenu(tr("&Game"),menuBar);

    actionCreateJoin = new QAction(tr("&Create/Join"),menuGame);
    actionExit = new QAction(tr("E&xit"),menuGame);
    
    view = new View(this, model);
    
    statusBar = new QStatusBar(this);

    menuGame->addAction(actionCreateJoin);
    menuGame->addAction(actionExit);
    menuBar->addMenu(menuGame);

    setMenuBar(menuBar);
    setCentralWidget(view);
    setStatusBar(statusBar);

    statusBar->showMessage(tr("Initializing game. Please wait..."));

    setMinimumSize(640,480);

    resize(1024,768);

    connect(actionCreateJoin,SIGNAL(triggered()),this,SLOT(hideWindowAndSwitch()));
    connect(actionExit,SIGNAL(triggered()),this,SLOT(exit()));

}

void GameWindow::hideWindowAndSwitch() {
    hide();
    emit switchToDialog();
}

void GameWindow::exit() {
    close();
}

void GameWindow::setStatus(QString status) {
    statusBar->showMessage(status,INT_MAX);
}

void GameWindow::redrawView(quint32 x, quint32 y) {
    view->setViewpoint(x,y);
    view->update();
}
