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

#include "SettingsDialog.h"
#include "SettingsModel.h"

class SettingsController : public QObject {

    Q_OBJECT

public:
    SettingsController(SettingsModel* _model, SettingsDialog* _dialog);
    virtual ~SettingsController();

    virtual QString initNetwork(bool create, quint32 port, QString host);

public slots:
    void disconnect();


signals:
    void startGame();

    void disconnected();

protected:
    SettingsModel* model;
    SettingsDialog* dialog;
};

#endif	/* _SETTINGSCONTROLLER_H */

