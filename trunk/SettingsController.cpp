/* 
 * File:   SettingsController.cpp
 * Author: pavel
 * 
 * Created on 31. březen 2010, 22:28
 */

#include <QWidget>

#include "SettingsController.h"

SettingsController::SettingsController(SettingsModel* _model, SettingsDialog* _dialog) {
    model = _model;
    dialog = _dialog;
}

SettingsController::~SettingsController() {
}

QString SettingsController::initNetwork(bool create, quint32 port, QString host) {

    // TODO initialize networking to allow settings, return error string (if any)

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

