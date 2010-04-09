/* 
 * File:   Validator.cpp
 * Author: pavel
 * 
 * Created on 30. březen 2010, 11:18
 */

#include "Initializer.h"

Initializer::Initializer() {
    evaluator = NULL;
}

void Initializer::initGUI() {

    comm = new Communicator(this);

    settingsModel = new SettingsModel(this);
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

    settingsModel->setStatus(tr("Starting game..."));
    settingsModel->setReady(false);
    settingsDialog->reload();

    if(settingsModel->isCreating()) {
        if(!evaluator) {
            evaluator = new Evaluator(this);
            evaluator->start();
        }
    }
    
    settingsDialog->hide();
    gameWindow->show();

    //TODO reconnect signals for disconnected sockets
}