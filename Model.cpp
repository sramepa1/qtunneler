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
#include <cmath>
#include <ctime>

#include <QBrush>
#include <QPen>
#include <QPainter>

/**
 * Consructs the model.
 *
 * @param parent
 */
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

    const uchar* data = getTunnelBitmapData(0,0,MATRIX_DIMENSION,MATRIX_DIMENSION);
    tunnelMap = new QBitmap(QBitmap::fromData(QSize(MATRIX_DIMENSION,MATRIX_DIMENSION),data,QImage::Format_MonoLSB));
    delete[] data;
}

/**
 * Destructs model.
 */
Model::~Model() {
    deleteObjectsInContainers();

    delete matrix;
    delete border;
    delete bases;
    delete solidObjects;
    delete projectiles;
    delete tanks;
    delete explosions;

    if(tunnelMap) delete tunnelMap;
}

/**
 * Delete objects stored in model's containers and the containers.
 */
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

/**
 * Reset the model to the state after the construction.
 */
void Model::reset() {

    qDebug("Model::reset()");

    deleteObjectsInContainers();

    matrix->reset();
    bases->clear();
    solidObjects->clear();

    tanks->clear();
    projectiles->clear();
    explosions->clear();

    playerID = NO_PLAYER;
    nextProjectileID = qrand();

    if(tunnelMap) delete tunnelMap;
    const uchar* data = getTunnelBitmapData(0,0,MATRIX_DIMENSION,MATRIX_DIMENSION);
    tunnelMap = new QBitmap(QBitmap::fromData(QSize(MATRIX_DIMENSION,MATRIX_DIMENSION),data,QImage::Format_MonoLSB));
    delete[] data;
}

/**
 * Returns cutted part of the matrix for needs of the View.
 *
 * @param x
 * @param y
 * @param width
 * @param height
 * @return
 */
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

/**
 * Returns vector of all Solid objects in given rectangle.
 *
 * @param x
 * @param y
 * @param width
 * @param height
 * @return
 */
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

/**
 * Return QRectangles representing border in given rectangle.
 *
 * @param x1
 * @param y1
 * @param width
 * @param height
 * @return
 */
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

/**
 * Returns vector of all shots in given rectangle.
 *
 * @param x
 * @param y
 * @param width
 * @param height
 * @return
 */
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

/**
 * Returns vector of all tanks in given rectangle.
 *
 * @param x
 * @param y
 * @param width
 * @param height
 * @return
 */
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

/**
 * Make tunel between tanks last and new position
 *
 * @param tankID
 * @param newX
 * @param newY
 */
void Model::maskMatrixWithTank(qint32 tankID, qint32 newX, qint32 newY) {
    Tank tank(*tanks->value(tankID));

    qint32 x1 = tank.getX();
    qint32 y1 = tank.getY();

    tank.setRadius(TANK_MASK_RADIUS);
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

    qint32 minX = std::min(x1,newX);
    qint32 minY = std::min(y1,newY);
    
    updateTunnelMap(minX - TANK_RADIUS, minY - TANK_RADIUS, std::max(x1,newX) - minX + 2*TANK_RADIUS, std::max(y1,newY) - minY + 2*TANK_RADIUS);
}

/**
 * Add base to gameplay area.
 *
 * @param _x
 * @param _y
 * @param _width
 * @param _height
 * @param _color
 * @param _wallColor
 */
void Model::addBase(qint32 _x, qint32 _y, qint32 _width, qint32 _height, quint8 _color, QColor _wallColor) {
    bases->append(new Base(_x, _y, _width, _height, _color));

    BaseWall * baseWall = new BaseWall(_x, _y, _width, _height, _wallColor);
    solidObjects->append(baseWall);
    matrix->maskMatrix(baseWall);
    updateTunnelMap(_x, _y, _width, _height);
}

/**
 * Checks if the given round object colides with matrix.
 *
 * @param obj
 * @return
 */
bool Model::isMatrixCollision (const RoundObj * obj) const{

    for (int i = obj->getX1(); i < obj->getX2(); i++) {
        for (int j = obj->getY1(); j < obj->getY2(); j++) {
            if(matrix->getXY(i, j) && obj->isWithinCircle(i, j)){
                return true;
            }
        }
    }

    return false;
}

/**
 * Checks if the given round object colides with some solid object.
 *
 * @param obj
 * @return
 */
bool Model::isSolidCollision (const RoundObj * obj) const{
    //Optimalized for common situlation
    //Could be contraproductive to totaly different world

    //Border collision
    if(border->isBorderCollision(obj)){
        return true;
    }

    //Solid objects collision
    foreach(BitmapObj * solid, *solidObjects){
        if(checkRectOverlap(obj->getX1() ,obj->getY1(), obj->getX2(), obj->getY2(), solid->getX1(), solid->getY1(), solid->getX2(), solid->getY2())){
            // 4 point optimalizatiom
            if(
                    solid->getXYGlobalCoordiantes(obj->getX1(), obj->getY()) ||
                    solid->getXYGlobalCoordiantes(obj->getX2(), obj->getY()) ||
                    solid->getXYGlobalCoordiantes(obj->getY1(), obj->getX()) ||
                    solid->getXYGlobalCoordiantes(obj->getY2(), obj->getX())
              )
            {
                return true;
            }

            //whole object inside solid - optimalization
            if(checkRectInsideRect(obj->getX1() ,obj->getY1(), obj->getX2(), obj->getY2(), solid->getX1(), solid->getY1(), solid->getX2(), solid->getY2())){
                for (int i = obj->getX1(); i < obj->getX2(); i++) {
                    for (int j = obj->getY1(); j < obj->getY2(); j++) {
                        //colides
                        if(obj->isWithinCircle(i, j) && solid->getXYGlobalCoordiantes(i, j)){
                            return true;
                        }
                    }
                }

            //colides with wrapper
            }else{
                for (int i = solid->getX1(); i < solid->getX2(); i++) {
                    //indexes optimalization
                    if(obj->getDistanceFormCenter(i, obj->getY()) > obj->getRadius()){
                        if(i < obj->getX1()){
                            i = obj->getX1();
                        }else{
                            break;
                        }
                    }

                    //univerasl search
                    for (int j = solid->getY1(); j < solid->getY2(); j++) {
                        if(obj->isWithinCircle(i, j) && solid->getXYGlobalCoordiantes(i, j)){
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}


/**
 * Checks if the given round object colides with some tank.
 *
 * @param obj
 * @return
 */
bool Model::isTankCollision (const RoundObj * obj) const{

    foreach(Tank * tank, *tanks){

        if(tank == obj){
            continue;
        }

        qint32 x1 = tank->getX();
        qint32 y1 = tank->getY();
        qint32 x2 = obj->getX();
        qint32 y2 = obj->getY();
        qint32 r1 = tank->getRadius();
        qint32 r2 = obj->getRadius();

        if(
                (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)
                <
                (r1 + r2) * (r1 + r2)
          )
        {
            return true;
        }
                
    }

    return false;
}

/**
 * Checks if the given @see Projectile colides with some tank.
 *
 * @param projectile
 * @return
 */
bool Model::isTankCollision (const Projectile * projectile) const{

    foreach(Tank * tank, *tanks){
        //No collision with dead tanks
        if(tank->hp <= 0){
            continue;
        }

        qint32 x1 = tank->getX();
        qint32 y1 = tank->getY();
        qint32 x2 = projectile->getX();
        qint32 y2 = projectile->getY();
        qint32 r1 = tank->getRadius();
        qint32 r2 = projectile->getRadius();

        if(
                (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)
                <
                (r1 + r2) * (r1 + r2)
          )
        {
            if(tank->id != projectile->tankID){
                //do not colide with own  tank
                return true;
            }
        }

    }

    return false;
}

/**
 * Checks if the given round object colides with some projectile.
 *
 * @param obj
 * @return
 */
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

/**
 * Checks if the given tank colides with another tank or solid object.
 *
 * @param obj
 * @return
 */
bool Model::isCollisionForTank (const Tank * obj) const{
    return isSolidCollision(obj) || isTankCollision(obj);
}

/**
 *  Checks if the given projectile colides with another projectile, matrix, tank or solid object.
 *
 * @param projectile
 * @return
 */
bool Model::isCollisionForProjectile (const Projectile * projectile) const{
    return isMatrixCollision(projectile) || isSolidCollision(projectile) || isTankCollision(projectile)/*|| isProjectileCollision(projectile)*/;
}

/**
 * Moves tank by default count of moves (per frame) as far as is possible.
 *
 * @param tank
 */
void Model::moveTankWhilePossible(Tank* tank) {

    QPair<qint32, qint32> coord = tank->getMoveCoorinates(TANK_SPEED);
    qint32 x = coord.first;
    qint32 y = coord.second;

    qint32 moves = TANK_SPEED;
    qint32 pixels = TANK_MAX_TUNNEL;
    bool canMove = true;

    while(tank->getX() != x || tank->getY() != y){
        if(moves > 0 && pixels > 0 && canMove){
            --moves;
            tank->move(1);
        }else{
            x = tank->getX();
            y = tank->getY();
            
            tank->energy -= TANK_ENERGY_COST_OF_MOVE;

            break;
        }

        if(isCollisionForTank(tank)){
            tank->move(-1);
            canMove = false;
        }

        if(isMatrixCollision(tank)){
            if(tank->isShoting){
                pixels -= TANK_MAX_TUNNEL / TANK_SPEED_FAST_TUNNELING;

            }else{
                pixels -= getPixelCountInCircle(tank);
            }

            tank->setRadius(TANK_MASK_RADIUS);
            for (int i = tank->getX1(); i < tank->getX2(); i++) {
                for (int j = tank->getY1(); j < tank->getY2(); j++) {
                    if(tank->isWithinCircle(i, j)){
                        matrix->setXY(i,j,false);
                    }
                }
            }
            tank->setRadius(TANK_RADIUS);

        }
        
    }

    tank->energy -= TANK_ENERGY_COST_OF_MOVE;
   
}

/**
 * Move tank to it's start position.
 */
void Model::moveTanksBackToBases() {

    foreach(Base* base, *bases) {
            Tank* t = tanks->value(base->color);
            t->setX(base->x1 + BASE_WIDTH/2);
            t->setY(base->y1 + BASE_HEIGHT/2);
            //rotation unchanged
    }
}

/**
 * Returns the count of solid pixels in matrix within a given round object.
 *
 * @param obj
 * @return
 */
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

/**
 * Check if the two given rectangles colides.
 *
 * @param x11
 * @param y11
 * @param x12
 * @param y12
 * @param x21
 * @param y21
 * @param x22
 * @param y22
 * @return
 */
bool Model::checkRectOverlap(qint32 x11, qint32 y11, qint32 x12, qint32 y12, qint32 x21, qint32 y21, qint32 x22, qint32 y22) const{

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

/**
 * Check the second rectangle is inside of the first one.
 *
 * @param x11
 * @param y11
 * @param x12
 * @param y12
 * @param x21
 * @param y21
 * @param x22
 * @param y22
 * @return
 */
bool Model::checkRectInsideRect(qint32 x11, qint32 y11, qint32 x12, qint32 y12, qint32 x21, qint32 y21, qint32 x22, qint32 y22) const{
    if(x11 >= x21 && x12 <= x22 && y11 >= y21 && y12 <= y22){
        return true;
    }

    return false;
}


/**
 * Creates QBitmap (cache) of tunel within given rectangle.
 *
 * @param x
 * @param y
 * @param width
 * @param height
 */
void Model::updateTunnelMap(qint32 x, qint32 y, qint32 width, qint32 height) {

    QPainter painter(tunnelMap);
    QPen blackPen;
    blackPen.setColor(Qt::black);

    QBrush whiteBrush;
    whiteBrush.setColor(Qt::white);
    whiteBrush.setStyle(Qt::SolidPattern);

    const uchar* data = getTunnelBitmapData(x,y,width,height);
    painter.setPen(blackPen);
    painter.setBackground(whiteBrush);
    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.drawPixmap(x,y,QBitmap::fromData(QSize(width,height),data,QImage::Format_MonoLSB));
    delete[] data;
}

const QBitmap* Model::getTunnelBitmap() const {
    return tunnelMap;
}