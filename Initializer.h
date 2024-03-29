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

class StartEvent : public QEvent {
public:
    StartEvent();
    static const QEvent::Type startType = static_cast<QEvent::Type>(2001);
};

/**
 * Class which responsibility is to initialize the program and start it's core.
 */
class Initializer : public QObject {

    Q_OBJECT

public:
    Initializer();
    virtual ~Initializer();
    
    virtual void startThreads();

    virtual bool event(QEvent* evt);

public slots:

    // initializes GUI-related members and shows form, wires signals between them
    virtual void initGUI();

    virtual void validate(InitVector vec);

    // Starts game core. Or REinitializes, core might already be present from last game.
    virtual void initCore();

    // Displays info message - generating world / receiving it
    virtual void displayInitInProgress();

    // Executes world initialization and starts actual game.
    virtual void startGame();

    // Displays a message box and then hides GameWindow and shows InitDialog. Final stats or error.
    virtual void endGame(QString message, bool ok);

    virtual void closeConnection();
    virtual void handleDisconnectInGame();

signals:
    void validated(QString message);


    void evalAddQueueRec(PacketQueue** qPtr);
    void evalAddNetRec(QTcpSocket* sock);
    void evalAddQueueSend(PacketQueue* q);
    void evalAddNetSend(QTcpSocket* sock);

    void ctrlSetQueueRec(PacketQueue** qPtr);
    void ctrlSetNetRec(QTcpSocket* sock);

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

    ControllerThread* controllerThread;
    EvaluatorThread* evalThread;

    int runningThreads;

    friend class Waiter;
};

class Waiter : public QThread {
    Q_OBJECT
public:
    Waiter(Initializer* i, QApplication* a) : init(i), app(a) {}
    virtual ~Waiter() {}
    virtual void run();
signals:
    void ready();
protected:
    Initializer* init;
    QApplication* app;
};

#endif	/* _INITIALIZER_H */

