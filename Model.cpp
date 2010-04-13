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

#include "Model.h"
#include "BaseWall.h"
#include "Stone.h"

Model::Model(QObject* parent) : QObject(parent) {
    qsrand( time(NULL) );

    matrix = new Matrix();
    border = new Border();

    bases = new QVector<Base*>();
    solidObjects = new QVector<BitmapObj*>();

    tanks = new QHash<qint32,Tank*>();
    projectiles = new QHash<qint32,Projectile*>();
    explosions = new QVector<Explosion*>();

    playerID = NO_PLAYER;

    nextProjectileID = qrand();

    playerColors[RED_PLAYER] = new QColor("red");
    playerColors[BLUE_PLAYER] = new QColor("blue");
    playerColors[GREEN_PLAYER] = new QColor("green");
}

Model::~Model() {
    deleteObjectsInContainers();

    delete matrix;
    delete border;
    delete bases;
    delete solidObjects;
    delete projectiles;
    delete tanks;
    delete explosions;
}

void Model::deleteObjectsInContainers(){
    //Delete bases
    foreach (Base * base, *bases) {
        delete base;
    }

    //Delete solidObjects
    foreach (BitmapObj * solidObject, *solidObjects) {
        delete solidObject;
    }

    //Delete projectiles
    foreach (Projectile * projectile, *projectiles) {
        delete projectile;
    }

    //Delete tanks
    foreach (Tank * tank, *tanks) {
        delete tank;
    }

    //Delete explosions
    foreach (Explosion * explosion, *explosions) {
        delete explosion;
    }
}

void Model::reset() {
    deleteObjectsInContainers();

    matrix->reset();
    bases->clear();
    solidObjects->clear();

    tanks->clear();
    projectiles->clear();
    explosions->clear();

    playerID = NO_PLAYER;
    nextProjectileID = qrand();
}

const uchar* Model::getTunnelBitmapData(qint32 x, qint32 y, qint32 width, qint32 height) const {
    
    uchar* buffer = new uchar [(width*height)/8 + height];
    uchar* ptr = buffer;

    uchar bit = 0;
    for(int j = y; j < y + height; j++) {
        for(int i = x; i < x + width; i++){
            *ptr = matrix->getXY(i,j) ? (*ptr & ~(1 << bit)) : ( *ptr | (1 << bit) );
            if(++bit > 7) {
                bit = 0;
                ptr++;
            }
        }
        if(bit != 0) { // last byte row padding
            bit = 0;
            ptr++;
        }
    }

    return buffer;    
}

bool checkRectOverlap(qint32 x11, qint32 y11, qint32 x12, qint32 y12, qint32 x21, qint32 y21, qint32 x22, qint32 y22);

QVector<BitmapObj*> Model::getSolidObjInRect(qint32 x, qint32 y, qint32 width, qint32 height) const {

    int size = solidObjects->size();
    QVector<BitmapObj*> vector;
    BitmapObj * obj;

    for (int i = 0; i < size; i++) {
        obj = solidObjects->at(i);

        if(checkRectOverlap(x, y, x + width, y + height, obj->getX1(), obj->getY1(), obj->getX2(), obj->getY2())){
            vector.append(obj);
        }
    }

    return vector;
}

QVector<QRect> Model::getBorderInRect(qint32 x1, qint32 y1, qint32 width, qint32 height) const{

    QVector<QRect> vector;
    
    qint32 x2 = x1 + width;
    qint32 y2 = y1 + height;

    //top rectangle
    if(checkRectOverlap(0, 0, MATRIX_DIMENSION, BORDER_SIZE,  x1, y1, x2, y2)){
        vector.append(QRect(QPoint(x1, y1), QPoint(x2, BORDER_SIZE)));
    }

    //rigth rectangle
    if(checkRectOverlap(MATRIX_DIMENSION - BORDER_SIZE, 0, MATRIX_DIMENSION, MATRIX_DIMENSION,  x1, y1, x2, y2)){
        vector.append(QRect(QPoint(MATRIX_DIMENSION - BORDER_SIZE, y1), QPoint(x2, y2)));
    }

    //bottum rectangle
    if(checkRectOverlap(0, MATRIX_DIMENSION - BORDER_SIZE, MATRIX_DIMENSION, MATRIX_DIMENSION,  x1, y1, x2, y2)){
        vector.append(QRect(QPoint(x1, MATRIX_DIMENSION - BORDER_SIZE), QPoint(x2, y2)));
    }

    //left rectangle
    if(checkRectOverlap(0, 0, BORDER_SIZE, MATRIX_DIMENSION,  x1, y1, x2, y2)){
        vector.append(QRect(QPoint(x1, y1), QPoint(BORDER_SIZE, y2)));
    }

    return vector;
}

QVector<QPoint> Model::getShotsInRect(qint32 x, qint32 y, qint32 width, qint32 height) const{

    qint32 x1 = (qint32)(x) - PROJECTILE_RADIUS;
    qint32 y1 = (qint32)(y) - PROJECTILE_RADIUS;
    qint32 x2 = x + width + PROJECTILE_RADIUS;
    qint32 y2 = y + height + PROJECTILE_RADIUS;

    QVector<QPoint> shots;

    foreach(Projectile * shot, *projectiles){
        if(shot->getX() > x1 && shot->getX() < x2 && shot->getY() > y1 && shot->getY() < y2){
            shots.append(QPoint(shot->getX(),shot->getY()));
        }
    }

    return shots;
}

QVector<OrientedRoundObj*> Model::getTanksInRect(qint32 x, qint32 y, qint32 width, qint32 height) const {

    QVector<OrientedRoundObj*> vector;

    qint32 x1 = (qint32)(x) - TANK_RADIUS;
    qint32 y1 = (qint32)(y) - TANK_RADIUS;
    qint32 x2 = x + width + TANK_RADIUS;
    qint32 y2 = y + height + TANK_RADIUS;

    foreach(Tank * tank, *tanks){
        if(tank->getX() > x1 && tank->getX() < x2 && tank->getY() > y1 && tank->getY() < y2){
            if(tank->hp > 0){ //alive tanks only
                vector.append(tank);
            }
        }
    }

    return vector;
}

void Model::maskMatrixWithTank(qint32 tankID, qint32 newX, qint32 newY) {
    Tank tank(*tanks->value(tankID));

    while(tank.getX() != newX || tank.getY() != newY){
        for (int i = tank.getX1(); i < tank.getX2(); i++) {
            for (int j = tank.getY1(); j < tank.getY2(); j++) {
                if(tank.isWithinCircle(i, j)){
                    matrix->setXY(i,j,false);
                }
            }
        }

        tank.move();
    }
}

void Model::addBase(qint32 _x, qint32 _y, qint32 _width, qint32 _height, quint8 _color, QColor _wallColor) {
    bases->append(new Base(_x, _y, _width, _height, _color));

    BaseWall * baseWall = new BaseWall(_x, _y, _width, _height, _wallColor);
    solidObjects->append(baseWall);
    matrix->maskMatrix(baseWall);
}

bool Model::isMatrixCollision (const RoundObj * obj) const{

    for (int i = obj->getX1(); i < obj->getX2(); i++) {
        for (int j = obj->getY1(); j < obj->getY2(); j++) {
            if(matrix->getXY(i, j) && obj->isWithinCircle(i, j)){
                return true
                        ;
            }
        }
    }

    return false;
}

bool Model::isSolidCollision (const RoundObj * obj) const{

    //TODO bug in base

    //Border collision
    if(border->isBorderCollision(obj)){
        return true;
    }

    //Solid objects collision

    foreach(BitmapObj * solid, *solidObjects){
        
        if(checkRectOverlap(obj->getX1() ,obj->getY1(), obj->getX2(), obj->getY2(), solid->getX1(), solid->getY1(), solid->getX2(), solid->getY2())){

            for (int i = obj->getX1(); i < obj->getX2(); i++) {
                for (int j = obj->getY1(); j < obj->getY2(); j++) {
                    //colides
                    if(obj->isWithinCircle(i, j) && solid->getXYGlobalCoordiantes(i, j)){
                        return true;
                    }
                }
            }
            
        }
    }

    return false;
}

bool Model::isTankCollision (const RoundObj * obj) const{

    foreach(Tank * tank, *tanks){

        if(tank == obj){
            continue;
        }

        if(checkRectOverlap(obj->getX1() ,obj->getY1(), obj->getX2(), obj->getY2(), tank->getX1(), tank->getY1(), tank->getX2(), tank->getY2())){

            for (int i = obj->getX1(); i < obj->getX2(); i++) {
                for (int j = obj->getY1(); j < obj->getY2(); j++) {
                    //colides
                    if(obj->isWithinCircle(i, j) && tank->isWithinCircle(i, j)){
                        return true;
                    }
                }
            }

        }
    }

    return false;
}

bool Model::isTankCollision (const Projectile * projectile) const{

    foreach(Tank * tank, *tanks){

        if(checkRectOverlap(projectile->getX1() ,projectile->getY1(), projectile->getX2(), projectile->getY2(), tank->getX1(), tank->getY1(), tank->getX2(), tank->getY2())){

            for (int i = projectile->getX1(); i < projectile->getX2(); i++) {
                for (int j = projectile->getY1(); j < projectile->getY2(); j++) {
                    //colides
                    if(projectile->isWithinCircle(i, j) && tank->isWithinCircle(i, j)){
                        if(tank->id != projectile->tankID){
                            //do not colide with own  tank
                            return true;
                        }
                    }
                }
            }

        }
    }

    return false;
}

bool Model::isProjectileCollision (const RoundObj * obj) const{

    foreach(Projectile * shot, *projectiles){

        if(shot == obj){
            continue;
        }

        if(checkRectOverlap(obj->getX1() ,obj->getY1(), obj->getX2(), obj->getY2(), shot->getX1(), shot->getY1(), shot->getX2(), shot->getY2())){

            for (int i = obj->getX1(); i < obj->getX2(); i++) {
                for (int j = obj->getY1(); j < obj->getY2(); j++) {
                    //colides
                    if(obj->isWithinCircle(i, j) && shot->isWithinCircle(i, j)){
                        return true;
                    }
                }
            }

        }
    }

    return false;
}

bool Model::isCollisionForTank (const Tank * obj) const{
    return isMatrixCollision(obj) || isSolidCollision(obj) || isTankCollision(obj) || isProjectileCollision(obj);
}

bool Model::isCollisionForProjectile (const Projectile * projectile) const{
    return isMatrixCollision(projectile) || isSolidCollision(projectile) || isTankCollision(projectile) || isProjectileCollision(projectile);
}

void Model::moveTankWhilePossible(Tank* tank) {

    // TODO implement
    QPair<qint32, qint32> coord = tank->getMoveCoorinates(16);

    maskMatrixWithTank(tank->id, coord.first, coord.second);

    tank->move(16);


    }

void Model::moveTanksBackToBases() {

    foreach(Base* base, *bases) {
            Tank* t = tanks->value(base->color);
            t->setX(base->x1 + BASE_WIDTH/2);
            t->setY(base->y1 + BASE_HEIGHT/2);
            //rotation unchanged
    }
}

qint32 Model::getPixelCountInCircle(const RoundObj * obj){
    RoundObj round(*obj);
    round.setRadius(round.getRadius() + 1);

    qint32 count = 0;

    for (int i = round.getX1(); i < round.getX2(); i++) {
        for (int j = round.getY1(); j < round.getY2(); j++) {
            if(round.isWithinCircle(i, j) && matrix->getXY(i,j)){
                ++count;
            }
        }
    }

    return count;
}

bool Model::checkRectOverlap(qint32 x11, qint32 y11, qint32 x12, qint32 y12, qint32 x21, qint32 y21, qint32 x22, qint32 y22) {

    if(x11 >= x21 && x12 > x22 && x11 < x22) { // a prekryva levou cast r
        if(y11 < y22 && y12 > y22 && y11 >= y21){ // levy dolni roh
            return true;
        }else if(y11 < y21 && y12 <= y22 && y12 > y21){ // levy horni roh
            return true;
        }else if(y11 >= y21 && y12 <= y22){ //cela leva cast
            return true;
        }else if(y11 < y21 && y12 > y22){ // zub v leve strane
            return true;
        }

    }else if(x11 < x21 && x12 <= x22 && x12 > x21) { // prava cast
        if(y11 < y22 && y12 > y22 && y11 >= y21){ // pravy dolni
            return true;
        }else if(y11 < y21 && y12 <= y22 && y12 > y21){ //pravy horni
            return true;
        }else if(y11 >= y21 && y12 <= y22){ // cela prava
            return true;
        }else if(y11 < y21 && y12 > y22){ // zub v prave
            return true;
        }

    }else if(x11 >= x21 && x12 <= x22) { // vodorovne uplne prekryti
        if(y11 < y22 && y12 > y22 && y11 >= y21){ //spodek
            return true;
        }else if(y11 < y21 && y12 <= y22 && y12 > y21){ //horejsek
            return true;
        }else if(y11 >= y21 && y12 <= y22){ // totalni prekryti
            return true;
        }else if(y11 < y21 && y12 > y22){ //vodorovny pruh
            return true;
        }

    }else if(x11 < x21 && x12 > x22) { //vodorovne a uvnitr r
        if(y11 < y22 && y12 > y22 && y11 >= y21){ // zub zespoda
            return true;
        }else if(y11 < y21 && y12 <= y22 && y12 > y21){ // zub zeshora
            return true;
        }else if(y11 >= y21 && y12 <= y22){ // svisly pruh
            return true;
        }else if(y11 < y21 && y12 > y22){ // maly uvnitr
            return true;
        }
    }

    return false;

}
