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

#ifndef _GAMEWINDOW_H
#define	_GAMEWINDOW_H

#include <QtGui>
#include <QObject>

#include "View.h"
#include "Model.h"

/**
 * Class of main game window where is the game played.
 */
class GameWindow : public QMainWindow {

    Q_OBJECT

public:
    GameWindow(Model* model, Clicker* clicker);
    virtual ~GameWindow() {}

    void focusKeyboard();

public slots:
    virtual void hideWindowAndSwitch();
    virtual void exit();

    void redrawViewToCenter(qint32 x, qint32 y);

    // sets statusbar message (near-permanent). Maybe replace with progressbars etc in version 2.0
    virtual void setStatus(QString status);

signals:
    void switchToDialog();
    void closeConnection();

protected:
    View* view;

    QMenuBar* menuBar;
    QMenu* menuGame;
    QAction* actionCreateJoin;
    QAction* actionExit;

    QStatusBar* statusBar;
};

#endif	/* _GAMEWINDOW_H */
