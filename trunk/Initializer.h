/* 
 * File:   Initializer.h
 * Author: pavel
 *
 * Created on 30. březen 2010, 11:18
 */

#ifndef _INITIALIZER_H
#define	_INITIALIZER_H

#include <QObject>
#include <QString>

#include "GameWindow.h"
#include "InitDialog.h"
#include "InitVector.h"
#include "SettingsModel.h"
#include "SettingsController.h"
#include "SettingsDialog.h"

class Initializer : public QObject {

    Q_OBJECT

public:
    Initializer() {}
    virtual ~Initializer() {}

    virtual void initGUI();

public slots:
    virtual void validate(InitVector vec);
    virtual void initCore();

signals:
    void validated(QString message);

protected:
    GameWindow* gameWindow;
    SettingsController* settingsController;
    SettingsDialog* settingsDialog;
    InitDialog* initDialog;

};

#endif	/* _INITIALIZER_H */

