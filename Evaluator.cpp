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

#include <ctime>

#include "Evaluator.h"
#include "BaseWall.h"

Evaluator::Evaluator(QObject* parent) : QObject(parent) {
    model = new Model(this);
    readyCnt = 0;
    connect(&timer,SIGNAL(timeout()),this,SLOT(evaluateState()));
}

Evaluator::~Evaluator() {
    disconnect(&timer,0,0,0);
    timer.stop();
    dumpSendersAndReceivers();
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
    model->reset();
    timer.stop();
    dumpSendersAndReceivers();
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

#ifdef DEBUG
    if(model->containerAccess.tryLock() == false){
        qDebug() << "Possible deadlock at" << __FILE__ << __LINE__;
        model->containerAccess.lock();
    }
#else
    model->containerAccess.lock();
#endif
#ifdef DEBUG
    qDebug() << "Mutex containerAccess locked at" << __FILE__ << __LINE__;
#endif

    qint32 x1, y1, x2, y2, width, heigth;

    x1 = (qint32) (((qreal) qrand() / RAND_MAX) * (MATRIX_DIMENSION - 2 * BASE_MIN_DISTANCE_FROM_BORDER - 2 * BORDER_SIZE) + BASE_MIN_DISTANCE_FROM_BORDER);
    y1 = (qint32) (((qreal) qrand() / RAND_MAX) * (MATRIX_DIMENSION - 2 * BASE_MIN_DISTANCE_FROM_BORDER - 2 * BORDER_SIZE) + BASE_MIN_DISTANCE_FROM_BORDER);

    do {
        x2 = (qint32) (((qreal) qrand() / RAND_MAX) * (MATRIX_DIMENSION - 2 * BASE_MIN_DISTANCE_FROM_BORDER - 2 * BORDER_SIZE) + BASE_MIN_DISTANCE_FROM_BORDER);
        y2 = (qint32) (((qreal) qrand() / RAND_MAX) * (MATRIX_DIMENSION - 2 * BASE_MIN_DISTANCE_FROM_BORDER - 2 * BORDER_SIZE) + BASE_MIN_DISTANCE_FROM_BORDER);

    }while(Model::checkRectOverlap(x1 - SCREEN / 2, y1 - SCREEN / 2 ,x1 + BASE_WIDTH + SCREEN / 2, y1 + BASE_HEIGHT + SCREEN / 2, x2 - SCREEN / 2, y2 - SCREEN / 2, x2 + BASE_WIDTH + SCREEN / 2, y2 + BASE_HEIGHT + SCREEN / 2));

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
            if(Model::checkRectOverlap(x1 - 3 * TANK_RADIUS, y1 -3 * TANK_RADIUS, x1 + width + 3 * TANK_RADIUS, y1 + heigth + 3 * TANK_RADIUS, base->x1, base->y1, base->x2, base->y2)){
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

    model->containerAccess.unlock();

#ifdef DEBUG
    qDebug() << "Mutex containerAccess unlocked at" << __FILE__ << __LINE__;
#endif

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
        QLinkedList<Packet>::iterator i = list.begin();
        while(i != list.end() && (*i).timecode <= p.timecode) { ++i; }
        list.insert(i,p);
    }
}

void Evaluator::evaluateState() {

#ifdef DEBUG
    if(model->containerAccess.tryLock() == false){
        qDebug() << "Possible deadlock at" << __FILE__ << __LINE__;
        model->containerAccess.lock();
    }
#else
    model->containerAccess.lock();
#endif
#ifdef DEBUG
    qDebug() << "Mutex containerAccess locked at" << __FILE__ << __LINE__;
#endif

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

    //Explode tanks with zero energy
    foreach(Tank * tank, *(model->tanks)) {
        if(tank->energy <= 0){
            tank->hp = 0;
            explode(tank);
        }
    }

    // move projectiles (and handle any resulting collisions & generate explosions)
    foreach(Projectile * projectile, *(model->projectiles)) {
        
        QPair<qint32, qint32> pair = projectile->getMoveCoorinates(PROJECTILE_SPEED);
        qint32 x = pair.first;
        qint32 y = pair.second;

        while(projectile->getX() != x || projectile->getY() != y) {

            projectile->move(1);

            if(model->isCollisionForProjectile(projectile)){
                explode(projectile);
                break;
            }
        }
    }

    foreach(Projectile * projectile, deletedProjectiles) {
        model->projectiles->remove(projectile->id);
        delete projectile;
    }

    deletedProjectiles.clear();
    hiddenTanks.clear();
    

    //all moving tanks, move!
    foreach(Tank* t, *(model->tanks)) {
        if(t->hp > 0){
            if(t->isMoving) {
                model->moveTankWhilePossible(t);
            }else {
                t->energy -= TANK_ENERGY_COST_OF_WAIT;
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
    }

    //all firing tanks, fire!!!
    QList<qint32> firedProjectiles;

    foreach (Tank * tank, *model->tanks) {
        if(tank->isShoting && tank->hp > 0){
            //qDebug("Tank ID %d is firing, tank orientation is %d",tank->id,(int)tank->rotation);
            Projectile * projectile = tank->fire(model->provideProjectileID());
            //qDebug("Shot ID %d fired,  projectile orientation %d",projectile->id,(int)projectile->rotation);
            model->projectiles->insert(projectile->id, projectile);
            firedProjectiles.append(projectile->id);
        }
    }
    // fired projectiles are spawned but not yet evaluated (will try to move next frame)

    //send new projectiles that survived evaluation
    foreach(quint32 id, firedProjectiles) {
        if(model->projectiles->contains(id)) {
            Projectile* p = model->projectiles->value(id);
            temp = Packet(OP_PROJECTILE,(qint32)p->rotation,p->id,p->getX(),p->getY());
            tempList.append(temp);
        }
    }

    // evaluate tank energy/HP gain from bases (distinguish own and enemy)
    foreach(Tank* t, *(model->tanks)) {
        foreach(Base* b, *(model->bases)) {
            if(b->isWithinBase(t->getX(),t->getY()) && t->hp > 0) { // replace with linear calculation?
                if(t->id == (qint32)b->color) {
                    t->hp += TANK_HP_GAIN_OWN_BASE;
                    t->energy += TANK_ENERGY_GAIN_OWN_BASE;
                }else {
                    t->hp += TANK_HP_GAIN_ENEMY_BASE;
                    t->energy += TANK_ENERGY_GAIN_ENEMY_BASE;
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
        if(t->hp > 0) {
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
        thread()->yieldCurrentThread();

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

    if(winner != NULL && winner->roundsWon >= MAX_WINS) {
        timer.stop(); // end game
    }else {
        timer.start(FRAME_MSECS); // new frame
    }

    model->containerAccess.unlock();

#ifdef DEBUG
    qDebug() << "Mutex containerAccess unlocked at" << __FILE__ << __LINE__;
#endif
}

void Evaluator::handleTankMovementChange(int tankID, int newDirection) {

    //qDebug("Changing movement status of tank %d, new direction in packet: %d",tankID,newDirection);

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
        if(t->turned) t->rotation = t->lastRotation;
        t->isMoving = false;
        t->turned = false;
    }else {
        if(dir == t->rotation) {
            t->isMoving = true;
            t->turned = false;
        }else {
            //qDebug("Setting rotation of tank %d to %d",t->id,(int)dir);
            t->lastRotation = t->rotation;
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

void Evaluator::explode(Projectile * projectile){
    Packet temp;

    if(deletedProjectiles.contains(projectile->id)){
        return;
    }
    deletedProjectiles.insert(projectile->id, projectile);

    Explosion explosion(projectile->getX(), projectile->getY(), projectile->color, qrand());

    temp = Packet(OP_EXPLOSION, explosion.seed, projectile->id, explosion.getX(), explosion.getY());
    tempList.append(temp);

    //Burn clue
    BitmapObj mask = explosion.getExplosionMask();
    model->matrix->invertMaskMatrix(& mask);

    //damage tanks within raius
    foreach(Tank * tank, *model->tanks){
        if(model->isTankCollision(& explosion) && tank->id != projectile->tankID){
            tank->hp -= explosion.countDamageToObj(tank);

            if(tank->hp <= 0){
                explode(tank);
            }
        }
    }

    //destroy shots within radius
    foreach(Projectile * shot, *model->projectiles){
        if(model->isProjectileCollision(& explosion) && shot->tankID != projectile->tankID){
            explode(shot);
        }
    }
                 
}

void Evaluator::explode(Tank * tank){
    Packet temp;

    if(hiddenTanks.contains(tank->id)){
        return;
    }
    hiddenTanks.insert(tank->id, tank);

    Explosion explosion(tank->getX(), tank->getY(), tank->color, qrand(), TANK_EXPLOSION_RADIUS);

    temp = Packet(OP_TANK_EXPLOSION, explosion.seed, tank->id, explosion.getX(), explosion.getY());
    tempList.append(temp);

    //Burn clue
    BitmapObj mask = explosion.getExplosionMask();
    model->matrix->invertMaskMatrix(& mask);

    //damage tanks within raius
    foreach(Tank * tank, *model->tanks){
        if(model->isTankCollision((& explosion))){
            tank->hp -= explosion.countDamageToObj(tank, TANK_EXPLOSION_DAMAGE);

            if(tank->hp <= 0){
                explode(tank);
            }
        }
    }

    //destroy shots within radius
    foreach(Projectile * shot, *model->projectiles){
        if(model->isProjectileCollision(& explosion) && shot->tankID != tank->id){
            explode(shot);
        }
    }

}
