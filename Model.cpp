/* 
 * File:   Model.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:33
 */

#include "Model.h"

#include <iostream>
#include <qt4/QtGui/qsystemtrayicon.h>

Model::Model(QObject* parent) : QObject(parent) {
    matrix = new Matrix();
    border = new Border();

    bases = new QVector<Base*>();
    solidObjects = new QVector<BitmapObj*>();

    tanks = new QHash<quint32,Tank*>();
    projectiles = new QHash<quint32,Projectile*>();
    explosions = new QHash<quint32,Explosion*>();

    //TODO fill the containers ???
}

Model::~Model() {
    delete matrix;
    delete border;

    //Delete bases
    for (int i = 0; i < bases->size(); i++) {
        delete (*bases)[i];
    }
    delete bases;

    //Delete vecObjects
    for (int i = 0; i < solidObjects->size(); i++) {
        delete (*solidObjects)[i];
    }
    delete solidObjects;

    //Delete tanks
    for (int i = 0; i < projectiles->size(); i++) {
        delete (*projectiles)[i];
    }
    delete projectiles;

    //Delete projectiles
    for (int i = 0; i < tanks->size(); i++) {
        delete (*tanks)[i];
    }
    delete tanks;

    //Delete explosions
    for (int i = 0; i < tanks->size(); i++) {
        delete (*explosions)[i];
    }
    delete explosions;
}

void Model::reset() {
    //TODO call destructor and constructor
}

const uchar* Model::getTunnelBitmapData(quint32 x, quint32 y, quint32 width, quint32 height) const {
    
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

bool checkRectOverlap(quint32 x11, quint32 y11, quint32 x12, quint32 y12, quint32 x21, quint32 y21, quint32 x22, quint32 y22);

QVector<BitmapObj*> Model::getSolidObjInRect(quint32 x, quint32 y, quint32 width, quint32 height) const {

    int size = solidObjects->size();
    QVector<const BitmapObj*> vector;
    const BitmapObj * obj;

    for (int i = 0; i < size; i++) {
        obj = solidObjects->at(i);

        if(checkRectOverlap(x, y, x + width, y + height, obj->getX1(), obj->getY1(), obj->getX2(), obj->getY2())){
            vector.append(obj);
        }
    }

    return QVector<BitmapObj*>(); //TODO return non-empty
}

QVector<QPoint> Model::getShotsInRect(quint32 x, quint32 y, quint32 width, quint32 height) const{

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

bool Model::isMatrixCollision (const RoundObj * obj){

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

bool Model::isSolidCollision (const RoundObj * obj){

    BitmapObj * solid;

    for (int h = 0; h < solidObjects->size(); h++) {
        solid = (*solidObjects)[h];
        
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

bool Model::isTankCollision (const RoundObj * obj){

    Tank * tank;

    for (int h = 0; h < tanks->size(); h++) {
        tank = (*tanks)[h];

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

bool Model::isProjectileCollision (const RoundObj * obj){

    Projectile * projectile;

    for (int h = 0; h < projectiles->size(); h++) {
        projectile = (*projectiles)[h];

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

bool Model::isAnyCollision (const RoundObj * obj){
    return isMatrixCollision(obj) || isSolidCollision(obj) || isTankCollision(obj) || isProjectileCollision(obj);
}

bool Model::checkRectOverlap(quint32 x11, quint32 y11, quint32 x12, quint32 y12, quint32 x21, quint32 y21, quint32 x22, quint32 y22) {

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


