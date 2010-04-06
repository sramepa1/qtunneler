/* 
 * File:   SettingsController.cpp
 * Author: pavel
 * 
 * Created on 31. březen 2010, 22:28
 */


#include <qt4/QtNetwork/qtcpserver.h>

#include "SettingsController.h"

SettingsController::SettingsController(SettingsModel* _model, SettingsDialog* _dialog) {
    model = _model;
    dialog = _dialog;
}

SettingsController::~SettingsController() {
}

QString SettingsController::initNetwork(bool create, quint16 port, QString host) {

    // TODO initialize networking to allow settings, return error string (if any)

    if(create) {
        //QTcpServer server = new QTcpServer();
        //TODO thread!!
    }else {

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

