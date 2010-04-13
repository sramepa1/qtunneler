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

#include "Initializer.h"
#include "QueueSender.h"
#include "QueueReceiver.h"
#include "NetReceiver.h"
#include "NetSender.h"

Initializer::Initializer() {
    evaluator = NULL;
}

void Initializer::initGUI() {

    comm = new Communicator(this);

    settingsModel = new SettingsModel(this);
    settingsDialog = new SettingsDialog(settingsModel);
    settingsController = new SettingsController(this,settingsModel,settingsDialog,comm);

    model = new Model(this);
    controller = new Controller(this,model);
    clicker = new Clicker(this,model);

    initDialog = new InitDialog();
    gameWindow = new GameWindow(model,clicker);

    initDialog->show();

    connect(initDialog,SIGNAL(switchToSettings()),settingsDialog,SLOT(showSettings()));
    connect(gameWindow,SIGNAL(switchToDialog()),initDialog,SLOT(showDialog()));

    connect(initDialog, SIGNAL(validateDialog(InitVector)), this, SLOT(validate(InitVector)));
    connect(this, SIGNAL(validated(QString)), initDialog, SLOT(validated(QString)));

    connect(controller,SIGNAL(initInProgress()),this,SLOT(displayInitInProgress()));
    connect(controller,SIGNAL(confirmInitEnd()),clicker,SLOT(confirmInitEnd()));

    connect(settingsDialog,SIGNAL(disconnect()),settingsController,SLOT(closeConnection()));
    connect(settingsController,SIGNAL(disconnected()),initDialog,SLOT(showDialog()));
    connect(settingsController,SIGNAL(connectionEstablished()),this,SLOT(initCore()));
   
    connect(controller,SIGNAL(endGame(QString,bool)),this,SLOT(endGame(QString,bool)),Qt::QueuedConnection);
    connect(controller,SIGNAL(status(QString)),gameWindow,SLOT(setStatus(QString)),Qt::QueuedConnection);
    connect(controller,SIGNAL(redrawToCenter(qint32,qint32)),gameWindow,SLOT(redrawViewToCenter(qint32,qint32)),Qt::QueuedConnection);

    connect(controller,SIGNAL(gameStarts()),this,SLOT(startGame()));
    connect(controller,SIGNAL(gameStarts()),clicker,SLOT(startClock()));

    connect(gameWindow,SIGNAL(closeConnection()),this,SLOT(closeConnection()));
}


void Initializer::validate(InitVector vec) {
    bool ok = false;
    qint32 port = vec.port.toUInt(&ok,10);
    if(!ok || port > 65535 || port == 0) {
        emit validated(vec.port + " is not a valid port number");
    } else {
        emit validated(settingsController->initNetwork(vec.create,(quint16)port,vec.host));
    }
}

void Initializer::initCore() {

    controller->resetStateAndStop();

    if(settingsModel->isCreating()) {
        if(!evaluator) {
            evaluator = new Evaluator(this);
            connect(settingsDialog,SIGNAL(startGame()),evaluator,SLOT(generateWorldAndStartRound()));
        }else {
            evaluator->clearStateAndStop();
        }

        evaluator->addSender(new NetSender(evaluator,comm->socket));
        evaluator->addReceiver(new NetReceiver(evaluator,comm->socket));

        PacketQueue* q = new PacketQueue();
        evaluator->addSender(new QueueSender(evaluator,q));
        controller->setReceiver(new QueueReceiver(controller,q));

        q = new PacketQueue();
        clicker->resetSender(new QueueSender(clicker,q));
        evaluator->addReceiver(new QueueReceiver(evaluator,q));

        evaluator->start();
    }else {
        controller->setReceiver(new NetReceiver(controller,comm->socket));
        clicker->resetSender(new NetSender(clicker,comm->socket));
    }

    controller->start(); 
}

void Initializer::displayInitInProgress() {
    settingsModel->setStatus(tr("Starting game..."));
    settingsModel->setReady(false);
    settingsDialog->reload();
}

void Initializer::startGame() {
    disconnect(comm->socket,SIGNAL(disconnected()),0,0);
    connect(comm->socket,SIGNAL(disconnected()),this,SLOT(handleDisconnectInGame()));

    settingsDialog->hide();
    gameWindow->show();
    gameWindow->focusKeyboard();
}

void Initializer::endGame(QString message, bool ok) {
    closeConnection();
    QMessageBox msgBox;
    msgBox.setText(ok ? tr("Finished") : tr("Error"));
    msgBox.setInformativeText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(ok ? QMessageBox::Information : QMessageBox::Critical);
    msgBox.exec();    
    controller->quit();
    if(evaluator) evaluator->quit();
    gameWindow->hide();
    initDialog->show();
}

void Initializer::handleDisconnectInGame() {
    closeConnection();
    endGame(tr("Connection has been lost."),false);
}

void Initializer::closeConnection() {
    disconnect(comm->socket,0,0,0);
    if(settingsModel->isCreating()) {
        comm->server->close();        
    }
    comm->socket->abort();
    comm->socket->close();
}