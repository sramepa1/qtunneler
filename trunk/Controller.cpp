/* 
 * File:   Controller.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:42
 */

#include "Controller.h"

Controller::Controller(QObject* parent, Model* _model) : QThread(parent) {
    receiver = NULL;
    model = _model;
    roundNr = 0; // init phase
}

Controller::~Controller() {
    quit();
    while(isRunning()) {}
}

void Controller::run() {
    exec();
}

void Controller::resetStateAndStop() {
    model->reset();
    quit();
}

void Controller::setReceiver(Receiver* r) {
    if(receiver != NULL) {
        disconnect(receiver,0,0,0);
        delete receiver;
    }
    receiver = r;
    connect(receiver,SIGNAL(packetReady(Receiver*)),this,SLOT(handlePacket(Receiver*)));
}

void Controller::handlePacket(Receiver* /*r*/) {

    //qDebug("controller got packet");
    Packet pack = receiver->getPacket();

    switch(pack.opcode) {
        case OP_INIT_START: emit initInProgress(); break;
        case OP_INIT_END: emit confirmInitEnd(); break;
        case OP_START_GAME: emit gameStarts(); break;

        case OP_TANK: handleTankMovement(pack.data1,pack.data2,pack.data3,pack.timecode); break;
        case OP_TANK_STATUS: handleTankStatus(pack.data1,pack.data2,pack.data3,pack.timecode); break;
        case OP_PROJECTILE: handleProjectileSpawn(pack.data1,pack.data2,pack.data3,pack.timecode); break;
        case OP_EXPLOSION: handleExplosion(pack.data1,pack.data2,pack.data3,pack.timecode); break;
        case OP_TANK_EXPLOSION: handleTankExplosion(pack.data1,pack.data2,pack.data3,pack.timecode); break;

        case OP_BASE: handleAddBase(pack.data1,pack.data2,pack.data3); break;
        case OP_STONE: handleAddStone(); break;

        case OP_FRAME_BOUNDARY: handleFrameBoundary(); break;
        case OP_END_GAME: handleEndGame(); break;

        case 424242: emit redrawToCenter(pack.data1,pack.data2);
    }
}

void Controller::handleTankMovement(qint32 tankID, qint32 x, qint32 y, qint32 rotation) {
    
    if(roundNr == 0) {
        if(model->playerID == NO_PLAYER) {
            model->playerID = tankID;
        }
        Tank* t = new Tank(x,y,(quint8)tankID,tankID);
        t->rotation = (OrientedRoundObj::direction)rotation;
        model->tanks->insert(tankID,t);
    }else {
        
        model->maskMatrixWithTank(tankID,x,y);
        Tank* t = model->tanks->value(tankID);
        t->setX(x);
        t->setY(y);
    }
}

void Controller::handleTankStatus(qint32 tankID, qint32 hp, qint32 energy, qint32 roundsWon) {

    Tank* t = model->tanks->value(tankID);
    t->hp = hp;
    t->energy = energy;
    t->roundsWon = roundsWon;
    if(tankID == model->playerID) {
        emit status(tr("HP: ") + QString::number((double)hp*100 / DEFAULT_TANK_HP,'f',0) + tr("% | Energy: ")
            + QString::number((double)energy*100 / DEFAULT_TANK_ENERGY,'f',0) + tr("% | Rounds won: ")
            + QString::number(roundsWon,10));
    }
}

void Controller::handleProjectileSpawn(qint32 projectileID, qint32 x, qint32 y, qint32 rotation) {

    model->projectiles->insert(projectileID, new Projectile(x,y,NO_PLAYER,projectileID,(OrientedRoundObj::direction)rotation));
    // TODO implement more ?

}

void Controller::handleExplosion(qint32 projectileID, qint32 x, qint32 y, qint32 srand) {

    // TODO implement

}

void Controller::handleTankExplosion(qint32 tankID, qint32 x, qint32 y, qint32 srand) {

    // TODO implement

}


void Controller::handleAddBase(qint32 tankID, qint32 x, qint32 y) {

    // TODO implement, base + basewall!

}

void Controller::handleAddStone() { // TODO parameters

    // TODO implement

}

void Controller::handleFrameBoundary() {

    // TODO implement

    emit redrawToCenter(model->tanks->value(model->playerID)->getX(),model->tanks->value(model->playerID)->getY());
}

void Controller::handleEndRound() {

    // TODO implement

}


void Controller::handleEndGame() {

    // TODO implement

}

