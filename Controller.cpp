/* 
 * File:   Controller.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:42
 */

#include "Controller.h"
#include "BaseWall.h"

Controller::Controller(QObject* parent, Model* _model) : QThread(parent) {
    receiver = NULL;
    model = _model;
    roundNr = 0; // init phase

    playerColors[RED_PLAYER] = new QColor("red");
    playerColors[BLUE_PLAYER] = new QColor("blue");
    playerColors[GREEN_PLAYER] = new QColor("green");
}

Controller::~Controller() {
    quit();
    while(isRunning()) {}
}

void Controller::run() {
    exec();
}

void Controller::resetStateAndStop() {
    //model->reset();                       TODO uncomment!!!!!!!! <<<<<<<<<<<<<<<<<<<<<<<<<<<
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

    model->containerAccess.lock();

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
        case OP_STONE: handleAddStone(pack.timecode,pack.data1,pack.data2,pack.data3); break;

        case OP_FRAME_BOUNDARY: handleFrameBoundary(); break;
        case OP_END_ROUND: handleEndRound(); break;
        case OP_END_GAME: handleEndGame(pack.data1); break;

        case 424242: emit redrawToCenter(pack.data1,pack.data2);
    }

    model->containerAccess.unlock();
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
        Tank* t = model->tanks->value(tankID);
        t->rotation = (OrientedRoundObj::direction)rotation;
        model->maskMatrixWithTank(tankID,x,y);
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
            + QString::number(roundsWon,10) + tr(" | Round: ") + QString::number(roundNr,10));
    }
}

void Controller::handleProjectileSpawn(qint32 projectileID, qint32 x, qint32 y, qint32 rotation) {

    model->projectiles->insert(projectileID, new Projectile(x,y,NO_PLAYER,projectileID,(OrientedRoundObj::direction)rotation));
}

void Controller::handleExplosion(qint32 projectileID, qint32 x, qint32 y, qint32 srand) {

    // TODO implement

}

void Controller::handleTankExplosion(qint32 tankID, qint32 x, qint32 y, qint32 srand) {

    // TODO implement

}


void Controller::handleAddBase(qint32 tankID, qint32 x, qint32 y) {

    model->bases->append(new Base(x,y,BASE_WIDTH,BASE_HEIGHT,(quint8)tankID));
    BaseWall* b = new BaseWall(x,y,BASE_WIDTH,BASE_HEIGHT,*(playerColors.value(tankID)));
    model->matrix->maskMatrix(b);
    model->solidObjects->append(b);
}

void Controller::handleAddStone(qint32 x, qint32 y, qint32 width, qint32 height) { // TODO parameters

    model->solidObjects->append(new Stone(x,y,width,height));
}

void Controller::handleFrameBoundary() {

    // TODO implement - move projectiles etc.

    emit redrawToCenter(model->tanks->value(model->playerID)->getX(),model->tanks->value(model->playerID)->getY());
}

void Controller::handleEndRound() {

    roundNr++;
    foreach(Base* base, *(model->bases)) {
        if(base->color == model->playerID) {
            Tank* t = model->tanks->value(model->playerID);
            t->setX(base->x1 + BASE_WIDTH/2);
            t->setY(base->y1 + BASE_HEIGHT/2);
            //rotation unchanged
            break;
        }
    }
}


void Controller::handleEndGame(qint32 tankID) {

    emit endGame(tr("Game finished. You have ") + (tankID==model->playerID ? tr("won!") : tr("lost.")),true);
}

