/* 
 * File:   Validator.cpp
 * Author: pavel
 * 
 * Created on 30. březen 2010, 11:18
 */

#include "InitDialog.h"
#include "GameWindow.h"
#include "Initializer.h"

void Initializer::initGUI() {

    GameWindow* gameWindow = new GameWindow();

    InitDialog* initDialog = new InitDialog();
    initDialog->show();

    connect(initDialog,SIGNAL(switchToWindow()),gameWindow,SLOT(showWindow()));
    connect(gameWindow,SIGNAL(switchToDialog()),initDialog,SLOT(showDialog()));

    connect(initDialog, SIGNAL(validateDialog(InitVector)), this, SLOT(validate(InitVector)));
    connect(this, SIGNAL(validated(QString)), initDialog, SLOT(validated(QString)));
    
}


void Initializer::validate(InitVector vec) {
    bool ok = false;
    quint32 port = vec.port.toUInt(&ok,10);
    if(!ok || port > 65535) {
        emit validated(vec.port + " is not a valid port number");
    } else {
        emit validated(initCore(vec.create,port,vec.host));
    }
}


QString Initializer::initCore(bool create, quint32 port, QString host){

    // TODO initialize app core, start with networking, return error string (if any)

    // TODO - or REinitialize, core might already be present from last game.

    return QString();
}

