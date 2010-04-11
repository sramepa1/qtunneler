/* 
 * File:   Model.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:33
 */

#include "Model.h"
#include "BaseWall.h"
#include "Stone.h"

#include <qt4/QtGui/qtextdocument.h>
#include <qt4/QtGui/qsystemtrayicon.h>

Model::Model(QObject* parent) : QObject(parent) {
    matrix = new Matrix();
    //border = new Border();

    bases = new QVector<Base*>();
    solidObjects = new QVector<BitmapObj*>();

    tanks = new QHash<qint32,Tank*>();
    projectiles = new QHash<qint32,Projectile*>();
    explosions = new QVector<Explosion*>();

    init();
}

Model::~Model() {
    delete matrix;
    //delete border;

    //Delete bases
    for (int i = 0; i < bases->size(); i++) {
        delete (*bases)[i];
    }
    delete bases;

    //Delete solidObjects
    for (int i = 0; i < solidObjects->size(); i++) {
        delete (*solidObjects)[i];
    }
    delete solidObjects;

    //Delete projectiles
    for (int i = 0; i < projectiles->size(); i++) {
        delete (*projectiles)[i];
    }
    delete projectiles;

    //Delete tanks
    for (int i = 0; i < tanks->size(); i++) {
        delete (*tanks)[i];
    }
    delete tanks;

    //Delete explosions
    for (int i = 0; i < explosions->size(); i++) {
        delete (*explosions)[i];
    }
    delete explosions;
}

void Model::init() {
    //TODO iniclialize game

    //Init ID Providers
    nextProjectileID = 0;

    // ----------------------Testing purposes

    //create bases and basewalls

    bases->append(new Base(400, 400, 240, 240, 1));

    BaseWall * baseWall = new BaseWall(400, 400, 240, 240);

    solidObjects->append(baseWall);
    matrix->maskMatrix(baseWall);

    // ...
    
    tanks->insert(1, new Tank(500,500,1,1));

    solidObjects->append(new Stone(300, 100, 77, 100));
 
    Explosion * ex = new Explosion(300,300,1,1,200);
    matrix->invertMaskMatrix(& ex->getExplosionMask());

    Projectile * pr = new Projectile(50, 50, 11, 11, NORTH);
    projectiles->insert(11, pr);

    projectileExplosion(11);


}

void Model::reset() {
    //TODO reset game - clean everything
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

    //chci znaménkové
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

bool Model::isMatrixCollision (const RoundObj * obj) const{

    for (int i = obj->getX1(); i < obj->getX2(); i++) {
        for (int j = obj->getY1(); j < obj->getY2(); j++) {
            //colides
            if(matrix->getXY(i, j) && obj->isWithinCircle(i, j)){
                return true;
            }
        }
    }

    return false;
}

bool Model::isSolidCollision (const RoundObj * obj) const{

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

bool Model::isProjectileCollision (const RoundObj * obj) const{

    foreach(Projectile * projectile, *projectiles){

        if(checkRectOverlap(obj->getX1() ,obj->getY1(), obj->getX2(), obj->getY2(), projectile->getX1(), projectile->getY1(), projectile->getX2(), projectile->getY2())){

            for (int i = obj->getX1(); i < obj->getX2(); i++) {
                for (int j = obj->getY1(); j < obj->getY2(); j++) {
                    //colides
                    if(obj->isWithinCircle(i, j) && projectile->isWithinCircle(i, j)){
                        return true;
                    }
                }
            }

        }
    }

    return false;
}

bool Model::isAnyCollision (const RoundObj * obj) const{
    return isMatrixCollision(obj) || isSolidCollision(obj) || isTankCollision(obj) || isProjectileCollision(obj);
}

void Model::projectileExplosion(qint32 shotID){
    Projectile * shot = projectiles->take(shotID);
    //make new explosion
    
    qint32 seed = 15;//TODO gain somehow
    
    Explosion * explosion = new Explosion(shot->getX(), shot->getY(), shot->color, seed);
    explosions->append(explosion);

    //Burn clue
    matrix->invertMaskMatrix(& explosion->getExplosionMask());

    //damage tanks within raius
    foreach(Tank * tank, *tanks){
        if(isTankCollision(explosion)){
            tank->hp -= explosion->countDamageToObj(tank);
            
            if(tank->hp < 0){
                tank->hp = 0;
                ; //TODO react - tank destroyed
            }
        }
    }

    //destroy projectiles within radius
    foreach(Projectile * projectile, *projectiles){
        if(isProjectileCollision(explosion)){
            projectiles->remove(projectile->id);
            delete projectile;
        }
    }
    
}

void Model::tankFire(qint32 tankID){
    Tank * tank = tanks->take(tankID);

    Projectile * projectile = new Projectile(tank->fire());

    projectiles->insert(projectile->id, projectile);
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

int Model::getFirstTankID() {

    // TODO implement

    return 42;
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
