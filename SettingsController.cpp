/* 
 * File:   SettingsController.cpp
 * Author: pavel
 * 
 * Created on 31. březen 2010, 22:28
 */

#include "SettingsController.h"


SettingsController::SettingsController(QObject* parent, SettingsModel* _model, SettingsDialog* _dialog, Communicator* _comm) : QObject(parent) {
    model = _model;
    dialog = _dialog;
    comm = _comm;
}

SettingsController::~SettingsController() {
}

QString SettingsController::initNetwork(bool create, quint16 port, QString host) {

    // TODO initialize networking to allow settings, return error string (if any)

    if(create) {        
        //comm->server->close();

    }else {        
        //comm->socket->abort();
        //comm->socket->connectToHost(host, port);

    }

    

    // TODO - or REinitialize, networking might already be present from last game.

    //success
    model->setCreating(create);
    return QString();
}

void SettingsController::disconnect() {

    // TODO
    dialog->hide();
    emit disconnected();
}

