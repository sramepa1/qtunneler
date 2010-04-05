/* 
 * File:   VectorObj.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:35
 */


#include "BitmapObj.h"

BitmapObj::BitmapObj() {
    
}

BitmapObj::BitmapObj(quint32 _x, quint32 _y,quint32 _width, quint32 _heigth) {
    x = _x;
    y = _y;
    width = _width;
    height = _heigth;

    bitmap = new quint8* [width / 8];
    for(quint32 i = 0; i < width / 8; i++) {
        bitmap[i] = new quint8[height];

        //TODO nastavit - z obrázku?
    }
}

BitmapObj::~BitmapObj() {
    for(quint32 i = 0; i < width / 8; i++) {
        delete bitmap[i];
    }
    delete bitmap;
}

quint8 BitmapObj::getByte(quint32 xDiv8, quint32 y) const {
    return bitmap[xDiv8][y];
}

bool BitmapObj::getXY(quint32 x, quint32 y) const {
    return ((bitmap[x / 8][y]) & (1 << x % 8) != 0);
}


void BitmapObj::setByte(quint32 xDiv8, quint32 y, quint8 val) {
    bitmap[xDiv8][y] = val;
}

void BitmapObj::setXY(quint32 x, quint32 y, bool val) {
    bitmap[x / 8][y] = val ? (bitmap[x / 8][y] | (1 << x % 8)) : (bitmap[x / 8][y] & (1 << x % 8));
}