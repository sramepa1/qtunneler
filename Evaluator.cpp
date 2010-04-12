/* 
 * File:   Evaluator.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:42
 */
#include <ctime>

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
           stones.append(new Stone(x1, y1, width, heigth));
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

        Packet p = list.first();
        //qDebug("Evaluating %d, data1 %d, data2 %d",p.opcode,p.data1,p.data2);

        switch(p.opcode) {
            case OP_MOVE:  handleTankMovementChange(p.data1,p.data2); break;
            case OP_SHOOT:  handleTankShootChange(p.data1,p.data2);
        }

        list.removeFirst();
    }

    // TODO all firing tanks, fire!!!

    // TODO move all new projectiles here (and handle any resulting collisions & generate explosions)

    // TODO execute all explosions - mask matrix, modify tank HPs

    // TODO check tank HPs for <= 0, remove tanks, generate any tankExplosions (and eval them, checking tank HP again)

    // TODO evaluate tank energy/HP gain from bases (distinguish own and enemy)

    // TODO check for victory condition - if there is one last tank standing, send OP_END_ROUND (and reset tanks) or OP_END_GAME
    //          otherwise send OP_FRAME_BOUNDARY


    // TODO remove this - testing code
//    x += dx;
//    y += dy;
//
//    Packet p(424242,0,x,y,0);
//    tempList.append(p);
    // end of test


    //send changes
    foreach(Packet pack, tempList ) {
        dispatchPacket(pack);
        //qDebug("Dispatched opcode %d, data1 %d, data2 %d",pack.opcode,pack.data1,pack.data2);
    }
    tempList.clear();

    foreach(Sender* sender, senders) sender->flush();
    timer.start(FRAME_MSECS);
}

void Evaluator::handleTankMovementChange(int tankID, int newDirection) {

    // TODO implement - check collisions, calculate energy cost, etc. then send (update) tank packet

    int step = 16;
    switch(newDirection) {
        case MOVE_STOP : dy = dx = 0; break;
        case MOVE_N : dy = -step; dx = 0; break;
        case MOVE_NE : dy = -step; dx = step; break;
        case MOVE_E : dy = 0; dx = step; break;
        case MOVE_SE : dy = dx = step; break;
        case MOVE_S : dy = step; dx = 0; break;
        case MOVE_SW : dy = step; dx = -step; break;
        case MOVE_W : dy = 0; dx = -step; break;
        case MOVE_NW : dy = dx = -step; break;
    }
}

void Evaluator::handleTankShootChange(int tankID, int newState) {

    // TODO implement, this is only temporary <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    Packet p = Packet(OP_FRAME_BOUNDARY);
    dispatchPacket(p);
}