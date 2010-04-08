/* 
 * File:   SettingsController.cpp
 * Author: pavel
 * 
 * Created on 31. březen 2010, 22:28
 */

#include "SettingsController.h"
#include "DefaultValues.h"

SettingsController::SettingsController(QObject* parent, SettingsModel* _model, SettingsDialog* _dialog, Communicator* _comm) : QObject(parent) {
    model = _model;
    dialog = _dialog;
    comm = _comm;
    connect(comm->server,SIGNAL(newConnection()),this,SLOT(handleIncomingConnection()));
}

SettingsController::~SettingsController() {
}

QString SettingsController::initNetwork(bool create, quint16 port, QString host) {

    if(create) {
        model->setPort(port);
        if(!initServer()) return comm->server->errorString();
        // server started
    }else {
        comm->socket->abort();
        comm->socket->connectToHost(host, port);
        if(!comm->socket->waitForConnected(CONNECTION_TIMEOUT)) return comm->socket->errorString();
        // TCP established
        if(!comm->socket->waitForReadyRead(CONNECTION_TIMEOUT)){
            comm->socket->abort();
            return tr("Server is not responding or is not a QTunneler server.");
        }
        QString response(comm->socket->readLine(SERVER_HELLO_BUFF_SIZE));
        if(response.compare(SERVER_HELLO) != 0) {
            comm->socket->abort();
            return tr("Not a QTunneler server.");
        }
        // Server OK
        comm->socket->write(QString(CLIENT_HELLO).toAscii());
        comm->socket->flush();
        model->setStatus(tr("Waiting for host to start game..."));
        // client successfuly connected
        connect(comm->socket,SIGNAL(disconnected()),this,SLOT(handleDisconnected()));
    }
    
    //success
    model->setCreating(create);
    return QString();
}

void SettingsController::closeConnection() {
    if(model->isCreating()) {
        comm->server->close();
    }
    comm->socket->abort();
    dialog->hide();
    emit disconnected();
}

void SettingsController::handleIncomingConnection() {
    //cleanup old socket
    comm->socket->abort();
    delete comm->socket;
    //get client
    comm->socket = comm->server->nextPendingConnection();
    comm->server->close();
    model->setStatus(tr("Client connected, testing..."));
    dialog->reload();
    //send hello
    comm->socket->write(QString(SERVER_HELLO).toAscii());
    comm->socket->flush();
    //test client
    if(!comm->socket->waitForReadyRead(CONNECTION_TIMEOUT)) {
        comm->socket->abort();
        initServer();
        return;
    }
    QString response(comm->socket->readLine(CLIENT_HELLO_BUFF_SIZE));
    if(response.compare(CLIENT_HELLO) != 0) {
        comm->socket->abort();
        initServer();
        return;
    }
    connect(comm->socket,SIGNAL(disconnected()),this,SLOT(handleDisconnected()));

    //client OK
    model->setStatus(tr("Ready to start game."));
    model->setReady(true);
    dialog->reload();    
}

void SettingsController::handleDisconnected() {
    if(model->isCreating()) {
        initServer();
        model->setReady(false);
    }else {
        model->setStatus(tr("Connection lost."));
        disconnect(comm->socket,0,this,0);
    }
    dialog->reload();
}

bool SettingsController::initServer() {
    comm->server->close();
    if(!comm->server->listen(QHostAddress::Any,model->getPort())) return false;
    model->setStatus(tr("Waiting for client to connect..."));
    disconnect(comm->socket,0,this,0);
    dialog->reload();
    return true;
}