/* 
 * File:   Controller.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:42
 */

#ifndef _CONTROLLER_H
#define	_CONTROLLER_H

#include <QtCore>

#include "DefaultValues.h"
#include "Receiver.h"
#include "Model.h"

class Controller : public QThread {

    Q_OBJECT

public:
    Controller(QObject* parent = NULL, Model* _model = NULL);
    virtual ~Controller();

    virtual void run();

    virtual void resetStateAndStop();

    virtual void setReceiver(Receiver* r);

public slots:

    virtual void handlePacket(Receiver* /*r*/);

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
    virtual void handleAddStone(); // TODO parameters

    virtual void handleFrameBoundary();
    virtual void handleEndRound();
    virtual void handleEndGame();

    Receiver* receiver;

    qint32 roundNr;

    // not owner
    Model* model;

private:    
    Controller(const Controller& orig) {} // disabled
};

#endif	/* _CONTROLLER_H */


