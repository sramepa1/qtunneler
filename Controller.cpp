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

    // TODO implement

}

void Controller::handleTankStatus(qint32 tankID, qint32 hp, qint32 energy, qint32 roundsWon) {

    // TODO implement

}

void Controller::handleProjectileSpawn(qint32 projectileID, qint32 x, qint32 y, qint32 rotation) {

    // TODO implement

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

}

void Controller::handleEndGame() {

    // TODO implement

}

