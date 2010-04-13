/*
 *      -----------------------------------------------
 *      QTunneler - a classic DOS game remake in QT
 *      -----------------------------------------------
 *
 *      semestral project for API programming course
 *      (Y36API) at the FEE CTU Prague
 *
 *      Created by:
 *           Pavel Sramek (sramepa1@fel.cvut.cz)
 *           Martin Smarda (smardmar@fel.cvut.cz)
 *
 *      March & April 2010
 *
 *      This is free software, licensed under GNU LGPL
 *      (GNU Lesser General Public License, version 3)
 *      http://www.gnu.org/licenses/lgpl.html
 *
 *      Project homepage:
 *      http://code.google.com/p/qtunneler/
 *
 *      Version 1.0
 *
 */

#include "GameWindow.h"
#include "DefaultValues.h"

GameWindow::GameWindow(Model* model,Clicker* clicker) {

    setWindowTitle(APP_NAME_STRING);

    menuBar = new QMenuBar(this);
    menuGame = new QMenu(tr("&Game"),menuBar);

    actionCreateJoin = new QAction(tr("&Create/Join"),menuGame);
    actionExit = new QAction(tr("E&xit"),menuGame);
    
    view = new View(this, model, clicker);
    
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
    emit closeConnection();
    emit switchToDialog();
}

void GameWindow::exit() {
    emit closeConnection();
    close();
}

void GameWindow::setStatus(QString status) {
    statusBar->showMessage(status,INT_MAX);
}

void GameWindow::redrawViewToCenter(qint32 x, qint32 y) {

    int _x = view->width()/2;
    int _y = view->height()/2;
    
    _x = x + _x >= MATRIX_DIMENSION ? MATRIX_DIMENSION - view->width() -1 : x-_x;
    _y = y + _y >= MATRIX_DIMENSION ? MATRIX_DIMENSION - view->height() - 1 : y-_y;

    view->setViewpoint(_x < 0 ? 0 : _x, _y < 0 ? 0 : _y);
    view->update();
}

void GameWindow::focusKeyboard() {
    view->setFocus();
    view->grabKeyboard();
}
