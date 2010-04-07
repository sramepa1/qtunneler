/* 
 * File:   SettingsController.h
 * Author: pavel
 *
 * Created on 31. březen 2010, 22:28
 */

#ifndef _SETTINGSCONTROLLER_H
#define	_SETTINGSCONTROLLER_H

#include <QObject>
#include <QString>
#include <QtNetwork>

#include "SettingsDialog.h"
#include "SettingsModel.h"
#include "Communicator.h"

class SettingsController : public QObject {

    Q_OBJECT

public:
    SettingsController(QObject* parent = NULL, SettingsModel* _model = NULL, SettingsDialog* _dialog = NULL, Communicator* _comm = NULL);
    virtual ~SettingsController();

    virtual QString initNetwork(bool create, quint16 port, QString host);

public slots:
    void disconnect();


signals:
    void startGame();

    void disconnected();

protected:
    SettingsModel* model;
    SettingsDialog* dialog;

    Communicator* comm;
};

#endif	/* _SETTINGSCONTROLLER_H */

