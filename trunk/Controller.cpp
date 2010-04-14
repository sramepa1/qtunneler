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


Controller::Controller(QObject* parent, Model* _model) : QObject(parent) {
    receiver = NULL;
    model = _model;
    roundNr = 0; // init phase
    moveProjectiles = false;

    stream = NULL;

    qDebug("Pa_Open - error code %d", (int)Pa_OpenDefaultStream(&stream, 0, 1, paInt16, 22050, 0, NULL, NULL));

    mapSoundFile("sounds/boom.wav",&boomWav,&boomSize);

    // unused in this build, but load anyway...
    mapSoundFile("sounds/fire.wav",&fireWav,&fireSize);
    mapSoundFile("sounds/hit.wav",&hitWav,&hitSize);
}

void Controller::mapSoundFile(QString filename, char** destPtr, qint64* sizePtr) {
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)) {
        int offset = 64; // wav header?
        *sizePtr = file.size() - offset;
        char* ptr = (char*)file.map(offset,*sizePtr);
        *destPtr = new char[*sizePtr];
        memcpy(*destPtr,ptr,*sizePtr);
        file.close();
        qDebug() << "file " <<  file.fileName() << " of size " << *sizePtr << " loaded.";
    }else {
        qDebug() << "file " <<  file.fileName() << " NOT LOADED, sound will be unavailable";
        *destPtr = NULL;
    }
}

Controller::~Controller() {

    if(fireWav != NULL) delete[] fireWav;
    if(hitWav != NULL) delete[] hitWav;
    if(boomWav != NULL) delete[] boomWav;

    if(stream != NULL) Pa_CloseStream(stream);
}

void Controller::resetStateAndStop() {
    model->reset();
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

    // frame boundary after tank explosion
    if(boom && moveProjectiles && stream != NULL) {

        // Blocking call. Multi-channel sound is quite complicated to write
        // and this also has the advantage of holding the view for a while
        // so that tank explosion is seen

        qDebug("Pa_Start - error code %d", (int)Pa_StartStream(stream));

        PaError err;
        qint16* ptr = (qint16*)boomWav;
        int frames = boomSize / 1024;
        for( int i=0; i < (boomSize/2); i += frames ) {
           err = Pa_WriteStream( stream, ptr + i, frames );
           if( err ) break;
        }
        qDebug("Pa_Stop - error code %d", (int)Pa_StopStream(stream));

    }
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
}

void Controller::handleExplosion(qint32 projectileID, qint32 x, qint32 y, qint32 srand) {

    // QTunneler2 : add explosion to model and draw, next frame - remove

    Explosion* ex = new Explosion(x,y,NO_PLAYER,srand);
    model->projectiles->remove(projectileID);
    model->matrix->invertMaskMatrix( (&(ex->getExplosionMask())) );
    delete ex;
}

void Controller::handleTankExplosion(qint32 /*tankID*/, qint32 x, qint32 y, qint32 srand) {

    // QTunneler2 : add explosion to model and draw, next frame - remove

    Explosion* ex = new Explosion(x,y,NO_PLAYER,srand,TANK_EXPLOSION_RADIUS);
    model->matrix->invertMaskMatrix( (&(ex->getExplosionMask())) );
    delete ex;

    boom = true;
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

