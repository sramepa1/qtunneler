/* 
 * File:   Evaluator.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:42
 */
#include <ctime>
#include <qt4/QtGui/qstyleoption.h>

#include "Evaluator.h"
#include "BaseWall.h"

Evaluator::Evaluator(QObject* parent) : QThread(parent) {
    model = new Model(this);
    readyCnt = 0;
    connect(&timer,SIGNAL(timeout()),this,SLOT(evaluateState()));


    //TODO remove
    x = 512;
    y = 388;
    dx = dy = 0;
}

Evaluator::~Evaluator() {
    dumpSendersAndReceivers();
    quit();
    while(isRunning()) {}
}

void Evaluator::run() {
    //enter event loop
    exec();
}

void Evaluator::dispatchPacket(Packet& packet) {
    foreach(Sender* s, senders) s->sendPacket(packet);
}

void Evaluator::addSender(Sender* s) {
    senders.push_back(s);
}

void Evaluator::addReceiver(Receiver* r) {
    receivers.push_back(r);
    connect(r,SIGNAL(packetReady(Receiver*)),this,SLOT(handlePacket(Receiver*)));
}

void Evaluator::clearStateAndStop() {
    readyCnt = 0;
    timer.stop();
    dumpSendersAndReceivers();
    quit();
}

void Evaluator::dumpSendersAndReceivers() {
    foreach(Sender* s,senders) {
        delete s;
    }
    senders.clear();
    foreach(Receiver* r,receivers) {
        disconnect(r,0,0,0);
        delete r;
    }
    receivers.clear();
}

void Evaluator::generateWorldAndStartRound() {

    //WORLD GENERATION

    //generate bases
    qsrand( time(NULL) );

    qint32 x1, y1, x2, y2, width, heigth;

    x1 = (qint32) (((qreal) qrand() / RAND_MAX) * (MATRIX_DIMENSION - 2 * BASE_MIN_DISTANCE_FROM_BORDER - 2 * BORDER_SIZE) + BASE_MIN_DISTANCE_FROM_BORDER);
    y1 = (qint32) (((qreal) qrand() / RAND_MAX) * (MATRIX_DIMENSION - 2 * BASE_MIN_DISTANCE_FROM_BORDER - 2 * BORDER_SIZE) + BASE_MIN_DISTANCE_FROM_BORDER);

    do {
        x2 = (qint32) (((qreal) qrand() / RAND_MAX) * (MATRIX_DIMENSION - 2 * BASE_MIN_DISTANCE_FROM_BORDER - 2 * BORDER_SIZE) + BASE_MIN_DISTANCE_FROM_BORDER);
        y2 = (qint32) (((qreal) qrand() / RAND_MAX) * (MATRIX_DIMENSION - 2 * BASE_MIN_DISTANCE_FROM_BORDER - 2 * BORDER_SIZE) + BASE_MIN_DISTANCE_FROM_BORDER);

    }while(Model::checkRectOverlap(x1, y1 ,x1 + BASE_WIDTH, y1 + BASE_HEIGHT, x2, y2 ,x2 + BASE_WIDTH, y2 + BASE_HEIGHT));

    model->addBase(x1, y1, BASE_WIDTH, BASE_HEIGHT, RED_PLAYER, *(model->playerColors.value(RED_PLAYER)));
    model->addBase(x2, y2, BASE_WIDTH, BASE_HEIGHT, BLUE_PLAYER, *(model->playerColors.value(BLUE_PLAYER)));

    //generate tanks
    model->tanks->insert(RED_PLAYER, new Tank(x1 + BASE_WIDTH / 2, y1 + BASE_HEIGHT / 2, RED_PLAYER, RED_PLAYER));
    model->tanks->insert(BLUE_PLAYER, new Tank(x2 + BASE_WIDTH / 2, y2 + BASE_HEIGHT / 2, BLUE_PLAYER, BLUE_PLAYER));

    //generate stones
    QVector<Stone *> stones;

    for (int i = 0; i < STONE_COUNT; i++) {
        x1 = (qint32) (((qreal) qrand() / RAND_MAX) * (MATRIX_DIMENSION - STONES_MAX_WIDTH * 8 - 2 * BORDER_SIZE) + BORDER_SIZE) ;
        y1 = (qint32) (((qreal) qrand() / RAND_MAX) * (MATRIX_DIMENSION - STONES_MAX_HEIGHT * 8 - 2 * BORDER_SIZE) + BORDER_SIZE);
        width = ( (qint32) (((qreal) qrand() / RAND_MAX) * STONES_MAX_WIDTH)) * 8 ;
        heigth = ( (qint32) (((qreal) qrand() / RAND_MAX) * STONES_MAX_HEIGHT)) * 8 ;

        //check bases colisions
        bool flag = true;
        foreach(Base * base, *model->bases){
            if(Model::checkRectOverlap(x1, y1, x1 + width, y1 + heigth, base->x1, base->y1, base->x2, base->y2)){
                flag = false;
            } 
        }

        if(flag){
           Stone * stone = new Stone(x1, y1, width, heigth);
           stones.append(stone);
           model->solidObjects->append(stone);
        }else{
           --i;
        }
    }

    //----------------------------------

    // PACKET DISPATCH
    
    Packet p(OP_INIT_START);
    dispatchPacket(p);
    foreach(Sender* s, senders) s->flush();

    foreach(Base* base, *(model->bases)) {
        p = Packet(OP_BASE,0,base->color,base->x1,base->y1);
        dispatchPacket(p);
    }
    foreach(Stone* stone, stones) {
        p = Packet(OP_STONE,stone->getX1(),stone->getY1(),stone->getWidth(),stone->getHeight());
        dispatchPacket(p);
    }

    // Tanks - bypass regular dispatcher - first tank sent = player tank
    // then just send all tanks everywhere, duplication does not matter
    QList<Tank*> tanks = model->tanks->values();
    Q_ASSERT(tanks.size() == senders.size());
    for(int i = 0; i < tanks.size(); i++) {
        Tank* t = tanks.value(i);
        p = Packet(OP_TANK,t->rotation,t->id,t->getX(),t->getY());
        senders[i]->sendPacket(p);
    }

    foreach(Tank* t, *(model->tanks)) {
        p = Packet(OP_TANK,t->rotation,t->id,t->getX(),t->getY());
        dispatchPacket(p);
        p = Packet(OP_TANK_STATUS,t->roundsWon,t->id,t->hp,t->energy);
        dispatchPacket(p);
    }

    p = Packet(OP_INIT_END);
    dispatchPacket(p);
    foreach(Sender* s, senders) s->flush();

    // will now wait for confirmations to arrive
}

void Evaluator::handlePacket(Receiver* r) {
    //qDebug("evaluator got packet");
    Packet p = r->getPacket();

    // handle init confirmation
    if(p.opcode == OP_INIT_CONFIRM && ++readyCnt == receivers.size()) {
        //qDebug("evaluator dispatching start packet");
        Packet temp(OP_START_GAME);
        dispatchPacket(temp);
        foreach(Sender* s, senders) s->flush();
        timer.start(FRAME_MSECS);

    // add to priority queue
    } else if(list.isEmpty()) {
        list.append(p);
    } else {
        QLinkedList<Packet>::iterator i = list.end();
        while(--i != list.begin() && (*i).timecode >= p.timecode) {}
        
        if(i != list.begin() || (*i).timecode <= p.timecode) {
            ++i;
        }
        list.insert(i,p);
    }
}

void Evaluator::evaluateState() {
    // evaluate packets
    Packet temp;
    while(!list.isEmpty()) {

        temp = list.first();

        switch(temp.opcode) {
            case OP_MOVE:  handleTankMovementChange(temp.data1,temp.data2); break;
            case OP_SHOOT:  handleTankShootChange(temp.data1,temp.data2);
        }

        list.removeFirst();
    }

    // TODO move projectiles here (and handle any resulting collisions & generate explosions)

    foreach(Projectile * projectile, *(model->projectiles)) {

        for (int i = 0; i < PROJECTILE_SPEED; i++) {

            projectile->move(1);

            if(model->isAnyCollisionExceptOwnTank(projectile)){

                Explosion explosion(projectile->getX(), projectile->getY(), projectile->color, projectile->id);;

                temp = Packet(OP_EXPLOSION, projectile->id, projectile->id, projectile->getX(), projectile->getY());
                tempList.append(temp);

                //Burn clue
                model->matrix->invertMaskMatrix((& explosion.getExplosionMask()));

                //damage tanks within raius
                foreach(Tank * tank, *model->tanks){
                    if(model->isTankCollision((& explosion))){
                        tank->hp -= explosion.countDamageToObj(tank);

                        if(tank->hp < 0){
                            tank->hp = 0;
                            //TODO react - tank destroyed
                        }
                    }
                }

                model->projectiles->remove(projectile->id);
                delete projectile;

                /*//destroy projectiles within radius
                //TODO change - chain effect
                foreach(Projectile * shot, *model->projectiles){
                    if(model->isProjectileCollision((& explosion))){
                        model->projectiles->remove(shot->id);
                        delete shot;
                    }
                }
                 * */

                break;

            }
        }
    }



    //all moving tanks, move!
    foreach(Tank* t, *(model->tanks)) {
        if(t->isMoving) {
            model->moveTankWhilePossible(t);
        }
        if(t->isMoving || t->turned) {
            Packet p(OP_TANK,(qint32)t->rotation,t->id,t->getX(),t->getY());
            tempList.append(p);
        }
        if(t->turned) {
            t->turned = false;
            t->isMoving = true;
        }
    }

    //all firing tanks, fire!!!
    QList<qint32> firedProjectiles;

    foreach (Tank * tank, *model->tanks) {
        if(tank->isShoting){
            Projectile * projectile = tank->fire(model->provideProjectileID());
            model->projectiles->insert(projectile->id, projectile);
            firedProjectiles.append(projectile->id);
        }
    }
    // fired projectiles are spawned but not yet evaluated (will try to move next frame)

    // TODO execute all explosions - mask matrix, modify tank HPs

    // TODO check tank HPs for <= 0, generate any tankExplosions (and eval them, checking tank HP again)

    //send new projectiles that survived evaluation
    foreach(quint32 id, firedProjectiles) {
        if(model->projectiles->contains(id)) {
            Projectile* p = model->projectiles->value(id);
            temp = Packet(OP_PROJECTILE,(qint32)p->rotation,p->id,p->getX(),p->getY());
            tempList.append(temp);
        }
    }  // TODO above - make sure that explosions are NOT generated for destroyed NEW projectiles!!!!! <<<<<<<<<<<<<<<<<<<<<<<<<<<<,,

    // evaluate tank energy/HP gain from bases (distinguish own and enemy)
    foreach(Tank* t, *(model->tanks)) {
        foreach(Base* b, *(model->bases)) {
            if(b->isWithinBase(t->getX(),t->getY()) && t->hp >= 0) { // replace with linear calculation?
                if(t->id == (qint32)b->color) {
                    t->hp += TANK_HP_GAIN_OWN_BASE;
                    t->energy += TANK_ENERGY_GAIN_OWN_BASE;
                }else {
                    t->hp += TANK_HP_GAIN_OWN_BASE;
                    t->energy += TANK_ENERGY_GAIN_OWN_BASE;
                }
                if(t->hp > DEFAULT_TANK_HP) t->hp = DEFAULT_TANK_HP;
                if(t->energy > DEFAULT_TANK_ENERGY) t->energy = DEFAULT_TANK_ENERGY;
                break;
            }
        }
    }
    // send tank status
    foreach(Tank* t, *(model->tanks)) {
        temp = Packet(OP_TANK_STATUS,t->roundsWon,t->id,t->hp,t->energy);
        tempList.append(temp);
    }

    // check for victory condition - if there is one last tank standing, wins round
    qint32 tanksAlive = 0;
    Tank* winner = NULL; // only holds winner if tanksAlive <= 0
    foreach(Tank* t, *(model->tanks)) {
        if(t->hp >= 0) {
            tanksAlive++;
            winner = t;
        }
    }
    if(tanksAlive <= 1 && winner != NULL) {
        winner->roundsWon++;
    }


    if(tanksAlive <= 1) {
        // insert extra frame to show this state
        temp = Packet(OP_FRAME_BOUNDARY);
        tempList.append(temp);
        flushPacketList();
        wait(FRAME_MSECS);

        if(winner != NULL && winner->roundsWon >= MAX_WINS) {   // end of game
            temp = Packet(OP_END_GAME,0,winner->id,0,0);
            tempList.append(temp);

        }else {                                                 // end of round
            model->moveTanksBackToBases();
            temp = Packet(OP_END_ROUND);
            tempList.append(temp);

            foreach(Tank* t, *(model->tanks)) {
                t->hp = DEFAULT_TANK_HP;
                t->energy = DEFAULT_TANK_ENERGY;
                temp = Packet(OP_TANK_STATUS,t->roundsWon,t->id,t->hp,t->energy);
                tempList.append(temp);
            }
        }
    }

    temp = Packet(OP_FRAME_BOUNDARY);
    tempList.append(temp);

    //send changes
    flushPacketList();

    timer.start(FRAME_MSECS);
}

void Evaluator::handleTankMovementChange(int tankID, int newDirection) {

    //qDebug("Changing movement status of tank %d, new direction=%d (net)",tankID,newDirection);

    Tank* t = model->tanks->value(tankID);
    OrientedRoundObj::direction dir = t->rotation;

    switch(newDirection) {
        case MOVE_N : dir = OrientedRoundObj::NORTH; break;
        case MOVE_NE : dir = OrientedRoundObj::NORTH_EAST; break;
        case MOVE_E : dir = OrientedRoundObj::EAST; break;
        case MOVE_SE : dir = OrientedRoundObj::SOUTH_EAST; break;
        case MOVE_S : dir = OrientedRoundObj::SOUTH; break;
        case MOVE_SW : dir = OrientedRoundObj::SOUTH_WEST; break;
        case MOVE_W : dir = OrientedRoundObj::WEST; break;
        case MOVE_NW : dir = OrientedRoundObj::NORTH_WEST;
    }

    if(newDirection == MOVE_STOP) {
        t->isMoving = false;
        t->turned = false;
    }else {
        if(dir == t->rotation) {
            t->isMoving = true;
            t->turned = false;
        }else {
            t->rotation = dir;
            t->turned = true;
        }
    }
}

void Evaluator::handleTankShootChange(int tankID, int newState) {

    model->tanks->value(tankID)->isShoting = (bool)newState;
    
}

void Evaluator::flushPacketList() {
    foreach(Packet pack, tempList ) {
        dispatchPacket(pack);
        //qDebug("Dispatched opcode %d, data1 %d, data2 %d",pack.opcode,pack.data1,pack.data2);
    }
    tempList.clear();
    foreach(Sender* sender, senders) sender->flush();
}
