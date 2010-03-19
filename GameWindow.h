/* 
 * File:   GameWindow.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 12:27
 */

#ifndef _GAMEWINDOW_H
#define	_GAMEWINDOW_H

#include "ui_GameWindow.h"

class GameWindow : public QMainWindow {
    Q_OBJECT
public:
    GameWindow();
    virtual ~GameWindow();
private:
    Ui::GameWindow widget;
};

#endif	/* _GAMEWINDOW_H */
