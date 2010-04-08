/* 
 * File:   Validator.cpp
 * Author: pavel
 * 
 * Created on 30. březen 2010, 11:18
 */

#include "Initializer.h"

void Initializer::initGUI() {

    comm = new Communicator(this);

    SettingsModel* settingsModel = new SettingsModel(this);
    settingsDialog = new SettingsDialog(settingsModel);
    settingsController = new SettingsController(this,settingsModel,settingsDialog,comm);

    model = new Model(this);

    initDialog = new InitDialog();
    gameWindow = new GameWindow(model);

    initDialog->show();

    connect(initDialog,SIGNAL(switchToSettings()),settingsDialog,SLOT(showSettings()));
    connect(gameWindow,SIGNAL(switchToDialog()),initDialog,SLOT(showDialog()));

    connect(initDialog, SIGNAL(validateDialog(InitVector)), this, SLOT(validate(InitVector)));
    connect(this, SIGNAL(validated(QString)), initDialog, SLOT(validated(QString)));

    connect(settingsDialog,SIGNAL(startGame()),this,SLOT(initCore()));
    connect(settingsController,SIGNAL(startGame()),this,SLOT(initCore()));

    connect(settingsDialog,SIGNAL(disconnect()),settingsController,SLOT(closeConnection()));
    connect(settingsController,SIGNAL(disconnected()),initDialog,SLOT(showDialog()));
    
}


void Initializer::validate(InitVector vec) {
    bool ok = false;
    quint32 port = vec.port.toUInt(&ok,10);
    if(!ok || port > 65535 || port == 0) {
        emit validated(vec.port + " is not a valid port number");
    } else {
        emit validated(settingsController->initNetwork(vec.create,(quint16)port,vec.host));
    }
}

void Initializer::initCore() {

    // TODO - start game core. Or REinitialize, core might already be present from last game.
    
    // data to do this - in settingsModel

    settingsDialog->hide();
    gameWindow->show();
}