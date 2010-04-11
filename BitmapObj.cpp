/* 
 * File:   VectorObj.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:35
 */


#include "BitmapObj.h"


BitmapObj::BitmapObj(qint32 _x, qint32 _y,qint32 _width, qint32 _heigth) {
    x = _x;
    y = _y;
    width = _width;
    height = _heigth;

    qbitmap = NULL;
    
    bitmap = new quint8* [width / 8  + ( width % 8 == 0 ? 0 : 1 )];
    for(qint32 i = 0; i < width / 8 + ( width % 8 == 0 ? 0 : 1 ); i++) {
        bitmap[i] = new quint8[height];
        
        for (int j = 0; j < height; j++) {
            bitmap[i][j] = 0x00;
        }
    }

}

BitmapObj::BitmapObj(const BitmapObj & orig) {
    x = orig.x;
    y = orig.y;
    width = orig.width;
    height = orig.height;
    color = orig.color;

    if(orig.qbitmap == NULL) {
        qbitmap = NULL;
    } else {
        qbitmap = new QBitmap(*orig.qbitmap);
    }

    bitmap = new quint8* [width / 8 + ( width % 8 == 0 ? 0 : 1 )];
    for(qint32 i = 0; i < width / 8 + ( width % 8 == 0 ? 0 : 1 ); i++) {
        bitmap[i] = new quint8[height];
    }

    for(int i = 0; i < width / 8 + ( width % 8 == 0 ? 0 : 1 ); i++) {
        for (int j = 0; j < height; j++) {
            bitmap[i][j] = orig.bitmap[i][j];
        }
    }
    
}

BitmapObj::~BitmapObj() {
    for(qint32 i = 0; i < width / 8 + ( width % 8 == 0 ? 0 : 1 ); i++) {
        delete[] bitmap[i];
    }
    delete[] bitmap;

    delete qbitmap;
}

quint8 BitmapObj::getByte(qint32 xDiv8, qint32 y) const {
    return bitmap[xDiv8][y];
}

bool BitmapObj::getXY(qint32 x, qint32 y) const {
    return (bitmap[x / 8][y]) & (1 << x % 8);
}

bool BitmapObj::getXYGlobalCoordiantes(qint32 _x, qint32 _y) const{
    return getXY(_x - x, _y - y);
}

void BitmapObj::setByte(qint32 xDiv8, qint32 y, quint8 val) {
    bitmap[xDiv8][y] = val;
}

void BitmapObj::setXY(qint32 x, qint32 y, bool val) {
    bitmap[x / 8][y] = val ? (bitmap[x / 8][y] | (1 << x % 8)) : (bitmap[x / 8][y] & ~(1 << x % 8));
}

 void BitmapObj::setXYGlobalCoordiantes(qint32 _x, qint32 _y, bool val){
     setXY(_x - x, _y - y, val);
 }

const QBitmap* BitmapObj::getQBitmap() {
    if(qbitmap == NULL){
        uchar* qbitmapdata = new uchar[(width*height)/8 + height];
        uchar* ptr = qbitmapdata;
        uchar bit = 0;
        for(int j = 0; j < height; j++) {
            for(int i = 0; i < width; i++){
                *ptr = getXY(i,j) ? ( *ptr | (1 << bit) ) : (*ptr & ~(1 << bit));
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
        qbitmap = new QBitmap(QBitmap::fromData(QSize(width,height),qbitmapdata,QImage::Format_MonoLSB));
        delete[] qbitmapdata;
    }

    return qbitmap;
}
