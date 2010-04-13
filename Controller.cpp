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

#include "Controller.h"
#include "BaseWall.h"

#include <QString>

#include <iostream>
#include <string>



// TODO play sounds from a separate thread!



Controller::Controller(QObject* parent, Model* _model) : QThread(parent) {
    receiver = NULL;
    model = _model;
    roundNr = 0; // init phase
    moveProjectiles = false;

    format.bits = 16;
    format.byte_format = AO_FMT_NATIVE;
    format.channels = 1;
    format.rate = 22050;

    int driver = ao_default_driver_id();

    audio = ao_open_live(driver, &format, NULL);

    if(audio == NULL) qDebug("ao_open_live failed with errno %d, ao_default_driver_id is %d",errno,driver);

    mapSoundFile("sounds/fire.wav",&fireWav,&fireSize);
    mapSoundFile("sounds/hit.wav",&hitWav,&hitSize);
    mapSoundFile("sounds/boom.wav",&boomWav,&boomSize);
}

void Controller::mapSoundFile(QString filename, char** destPtr, qint64* sizePtr) {
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)) {
        *sizePtr = file.size();
        *destPtr = (char*)file.map(0,*sizePtr);
        file.close();
        qDebug() << "file " <<  file.fileName() << " of size " << *sizePtr << " loaded.";
    }else {
        qDebug() << "file " <<  file.fileName() << " NOT LOADED, sound will be unavailable";
        *destPtr = NULL;
    }
}

Controller::~Controller() {
    quit();
    while(isRunning()) {}

    delete[] fireWav;
    delete[] hitWav;
    delete[] boomWav;

    if(audio != NULL) ao_close(audio);
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

    model->containerAccess.lock();

    if(moveProjectiles) {
        foreach(Projectile* p, *(model->projectiles)) {
            p->move(PROJECTILE_SPEED);
        }
        moveProjectiles = false;
    }

    switch(pack.opcode) {
        case OP_INIT_START: emit initInProgress(); break;
        case OP_INIT_END: emit confirmInitEnd(); break;
        case OP_START_GAME: roundNr = 1; emit gameStarts(); break;

        case OP_TANK: handleTankMovement(pack.data1,pack.data2,pack.data3,pack.timecode); break;
        case OP_TANK_STATUS: handleTankStatus(pack.data1,pack.data2,pack.data3,pack.timecode); break;
        case OP_PROJECTILE: handleProjectileSpawn(pack.data1,pack.data2,pack.data3,pack.timecode); break;
        case OP_EXPLOSION: handleExplosion(pack.data1,pack.data2,pack.data3,pack.timecode); break;
        case OP_TANK_EXPLOSION: handleTankExplosion(pack.data1,pack.data2,pack.data3,pack.timecode); break;

        case OP_BASE: handleAddBase(pack.data1,pack.data2,pack.data3); break;
        case OP_STONE: handleAddStone(pack.timecode,pack.data1,pack.data2,pack.data3); break;

        case OP_FRAME_BOUNDARY: handleFrameBoundary(); break;
        case OP_END_ROUND: handleEndRound(); break;
        case OP_END_GAME: handleEndGame(pack.data1);
    }

    model->containerAccess.unlock();
}

void Controller::handleTankMovement(qint32 tankID, qint32 x, qint32 y, qint32 rotation) {
    
    if(model->tanks->contains(tankID)) {
        Tank* t = model->tanks->value(tankID);
        t->rotation = (OrientedRoundObj::direction)rotation;
        model->maskMatrixWithTank(tankID,x,y);
        t->setX(x);
        t->setY(y);
    }else {
        if(model->playerID == NO_PLAYER) {
            model->playerID = tankID;
            qDebug("Set playerID to %d",model->playerID);
        }
        Tank* t = new Tank(x,y,(quint8)tankID,tankID);
        t->rotation = (OrientedRoundObj::direction)rotation;
        model->tanks->insert(tankID,t);
        qDebug("Added tank of id %d to x=%d, y=%d",tankID,x,y);
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

    //if(fireWav != NULL) ao_play(audio, fireWav, (uint_32) fireSize);
}

void Controller::handleExplosion(qint32 projectileID, qint32 x, qint32 y, qint32 srand) {

    // QTunneler2 : add explosion to model and draw, next frame - remove

    Explosion* ex = new Explosion(x,y,NO_PLAYER,srand);
    model->projectiles->remove(projectileID);
    model->matrix->invertMaskMatrix( (&(ex->getExplosionMask())) );
    delete ex;

    //if(hitWav != NULL) qDebug("%d",ao_play(audio, hitWav, (uint_32) hitSize));
}

void Controller::handleTankExplosion(qint32 /*tankID*/, qint32 x, qint32 y, qint32 srand) {

    // QTunneler2 : add explosion to model and draw, next frame - remove

    Explosion* ex = new Explosion(x,y,NO_PLAYER,srand,TANK_EXPLOSION_RADIUS);
    model->matrix->invertMaskMatrix( (&(ex->getExplosionMask())) );
    delete ex;

    //if(boomWav != NULL) ao_play(audio, boomWav, (uint_32) boomSize);
}


void Controller::handleAddBase(qint32 tankID, qint32 x, qint32 y) {
    qDebug("Adding base of id %d to x=%d, y=%d",tankID,x,y);
    model->addBase(x,y,BASE_WIDTH,BASE_HEIGHT,(quint8)tankID,*(model->playerColors.value(tankID)));
}

void Controller::handleAddStone(qint32 x, qint32 y, qint32 width, qint32 height) {
    model->solidObjects->append(new Stone(x,y,width,height));
}

void Controller::handleFrameBoundary() {

    emit redrawToCenter(model->tanks->value(model->playerID)->getX(),model->tanks->value(model->playerID)->getY());

    moveProjectiles = true; // delay to next packet
}

void Controller::handleEndRound() {

    roundNr++;
    model->moveTanksBackToBases();
}


void Controller::handleEndGame(qint32 tankID) {

    emit endGame(tr("Game finished. You have ") + (tankID==model->playerID ? tr("won!") : tr("lost.")),true);
}

