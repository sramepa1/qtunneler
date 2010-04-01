/* 
 * File:   GameWindow.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 12:27
 */

#ifndef _GAMEWINDOW_H
#define	_GAMEWINDOW_H

#include <QtGui>
#include <QObject>

class GameWindow : public QMainWindow {

    Q_OBJECT

public:
    GameWindow();
    virtual ~GameWindow() {}

public slots:
    virtual void hideWindowAndSwitch();
    virtual void exit();

signals:
    void switchToDialog();

protected:
    QWidget* drawArea;

    QMenuBar* menuBar;
    QMenu* menuGame;
    QAction* actionCreateJoin;
    QAction* actionExit;

    QStatusBar* statusBar;
};

#endif	/* _GAMEWINDOW_H */
