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

#include "Communicator.h"
#include "Clicker.h"
#include "Controller.h"
#include "Evaluator.h"
#include "Model.h"



class Initializer : public QObject {

    Q_OBJECT

public:
    Initializer();
    virtual ~Initializer() {}

    // initializes GUI-related members and shows form, wires signals between them
    virtual void initGUI();

public slots:
    virtual void validate(InitVector vec);

    // Starts game core. Or REinitializes, core might already be present from last game.
    virtual void initCore();

    // Displays a message box and then hides GameWindow and shows InitDialog. Final stats or error.
    virtual void endGame(QString message, bool ok);

    virtual void handleDisconnectInGame();

signals:
    void validated(QString message);

protected:
    GameWindow* gameWindow;
    InitDialog* initDialog;

    SettingsController* settingsController;
    SettingsDialog* settingsDialog;
    SettingsModel* settingsModel;

    Communicator* comm;

    Model* model;
    Controller* controller;
    Evaluator* evaluator;
    Clicker* clicker;

};

#endif	/* _INITIALIZER_H */

