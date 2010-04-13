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


    // initializes networking to allow settings, return error string (if any)
    //      - or REinitializes, networking might already be present from last game.
    virtual QString initNetwork(bool create, quint16 port, QString host);

public slots:
    virtual void closeConnection();

    virtual void handleIncomingConnection();
    virtual void handleDisconnected();


signals:

    void connectionEstablished();

    void disconnected();

protected:

    virtual bool initServer();

    SettingsModel* model;
    SettingsDialog* dialog;

    Communicator* comm;
};

#endif	/* _SETTINGSCONTROLLER_H */

