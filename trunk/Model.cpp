/* 
 * File:   Model.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:33
 */

#include "Model.h"

#include <iostream>

Model::Model() {
    matrix = new Matrix();
    border = new Border();

    bases = new QVector<Base*>();
    bitmapObjects = new QVector<BitmapObj*>();

    roundObjects = new QHash<quint32,RoundObj*>();

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
    for (int i = 0; i < bitmapObjects->size(); i++) {
        delete (*bitmapObjects)[i];
    }
    delete bitmapObjects;

    //Delete roundObjects
    for (int i = 0; i < roundObjects->size(); i++) {
        delete (*roundObjects)[i];
    }
    delete roundObjects;
}

void Model::reset() {
    //TODO call destructor and constructor
}

const uchar* Model::getTunnelBitmapData(quint32 x, quint32 y, quint32 width, quint32 height) {
    
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

QVector<BitmapObj*> Model::getBitmapsInRect(quint32 x, quint32 y, quint32 width, quint32 height) {

    int size = bitmapObjects->size();
    QVector<const BitmapObj*> vector;
    const BitmapObj * obj;

    for (int i = 0; i < size; i++) {
        obj = bitmapObjects->at(i);

        if(checkRectOverlap(x, y, x + width, y + height, obj->getWrapperX1(), obj->getWrapperY1(), obj->getWrapperX2(), obj->getWrapperY2())){
            vector.append(obj);
        }
    }

    return QVector<BitmapObj*>();
}

bool checkRectOverlap(quint32 x11, quint32 y11, quint32 x12, quint32 y12, quint32 x21, quint32 y21, quint32 x22, quint32 y22) {

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