/* 
 * File:   Validator.cpp
 * Author: pavel
 * 
 * Created on 30. březen 2010, 11:18
 */

#include "InitDialog.h"
#include "GameWindow.h"
#include "Initializer.h"
#include "SettingsDialog.h"
#include "SettingsController.h"

void Initializer::initGUI() {

    SettingsModel* settingsModel = new SettingsModel();
    settingsDialog = new SettingsDialog(settingsModel);
    settingsController = new SettingsController(settingsModel,settingsDialog);

    initDialog = new InitDialog();
    gameWindow = new GameWindow(model);

    initDialog->show();

    connect(initDialog,SIGNAL(switchToSettings()),settingsDialog,SLOT(showSettings()));
    connect(gameWindow,SIGNAL(switchToDialog()),initDialog,SLOT(showDialog()));

    connect(initDialog, SIGNAL(validateDialog(InitVector)), this, SLOT(validate(InitVector)));
    connect(this, SIGNAL(validated(QString)), initDialog, SLOT(validated(QString)));

    connect(settingsDialog,SIGNAL(startGame()),this,SLOT(initCore()));
    connect(settingsController,SIGNAL(startGame()),this,SLOT(initCore()));

    connect(settingsDialog,SIGNAL(disconnect()),settingsController,SLOT(disconnect()));
    connect(settingsController,SIGNAL(disconnected()),initDialog,SLOT(showDialog()));
    
}


void Initializer::validate(InitVector vec) {
    bool ok = false;
    quint32 port = vec.port.toUInt(&ok,10);
    if(!ok || port > 65535) {
        emit validated(vec.port + " is not a valid port number");
    } else {
        emit validated(settingsController->initNetwork(vec.create,port,vec.host));
    }
}

void Initializer::initCore() {

    // TODO - start game core. Or REinitialize, core might already be present from last game.
    
    // data to do this - in settingsModel

    settingsDialog->hide();
    gameWindow->show();
}