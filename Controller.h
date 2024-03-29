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

#ifndef _CONTROLLER_H
#define	_CONTROLLER_H

#include <QtCore>

#include "DefaultValues.h"
#include "Receiver.h"
#include "Model.h"
#include "NetReceiver.h"

#if portaudio
#include <portaudio.h>
#endif

class Controller : public QObject {

    Q_OBJECT

public:
    Controller(QObject* parent = NULL, Model* _model = NULL);
    virtual ~Controller();

    virtual void resetState();

    virtual void setReceiver(Receiver* r);

public slots:

    virtual void handlePacket(Receiver* /*r*/);


    // init phase slots

    virtual void setNetReceiver(QTcpSocket* sock) {
        setReceiver(new NetReceiver(this,sock));
    }

    virtual void setQueueReceiver(PacketQueue** queuePtr) {
        *queuePtr = new PacketQueue();
        setReceiver(new QueueReceiver(this,*queuePtr));
    }

signals:

    void initInProgress();
    void confirmInitEnd();
    void gameStarts();

    void redrawToCenter(qint32 x, qint32 y);

    void status(QString status);

    void endGame(QString message, bool ok);

protected:

    virtual void handleTankMovement(qint32 tankID, qint32 x, qint32 y, qint32 rotation);
    virtual void handleTankStatus(qint32 tankID, qint32 hp, qint32 energy, qint32 roundsWon);
    virtual void handleProjectileSpawn(qint32 projectileID, qint32 x, qint32 y, qint32 rotation);
    virtual void handleExplosion(qint32 projectileID, qint32 x, qint32 y, qint32 srand);
    virtual void handleTankExplosion(qint32 tankID, qint32 x, qint32 y, qint32 srand);

    virtual void handleAddBase(qint32 tankID, qint32 x, qint32 y);
    virtual void handleAddStone(qint32 x, qint32 y, qint32 width, qint32 height);

    virtual void handleFrameBoundary();
    virtual void handleEndRound();
    virtual void handleEndGame(qint32 tankID);

    // not owner
    Model* model;

    Receiver* receiver;

    qint32 roundNr;

    bool moveProjectiles;
    bool boom;

#if portaudio
    virtual void mapSoundFile(QString filename, char** destPtr, qint64* sizePtr);

    virtual void playSoundBlocking(void* dataPtr, qint64 size);  
    
    char* fireWav;
    qint64 fireSize;

    char* hitWav;
    qint64 hitSize;

    char* boomWav;
    qint64 boomSize;

    PaStream* stream;
#endif

private:    
    Controller(const Controller& /*orig*/) : QObject() {} // disabled
};





class ControllerThread : public QThread {

    Q_OBJECT

public:
    ControllerThread(QObject* parent = NULL) : QThread(parent) {}
    virtual ~ControllerThread() {
        delete model;
        delete controller;
    }

    virtual void run() {
        model = new Model(NULL);
        controller = new Controller(NULL,model);
        yieldCurrentThread();
        exec();
    }

    virtual Controller* getController() { return controller; }
    virtual Model* getModel() { return model; }

protected:

    Controller* controller;
    Model* model;

};

#endif	/* _CONTROLLER_H */