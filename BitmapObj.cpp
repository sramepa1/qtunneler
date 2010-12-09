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

#include "BitmapObj.h"

/**
 * Construct the bitmap object with no solid part.
 *
 * @param _x
 * @param _y
 * @param _width
 * @param _height
 */
BitmapObj::BitmapObj(qint32 _x, qint32 _y,qint32 _width, qint32 _height) {
    x = _x;
    y = _y;
    width = _width;
    height = _height;

    qbitmap = NULL;
    
    bitmap = new quint8* [width / 8  + ( width % 8 == 0 ? 0 : 1 )];
    for(qint32 i = 0; i < width / 8 + ( width % 8 == 0 ? 0 : 1 ); i++) {
        bitmap[i] = new quint8[height];
        
        for (int j = 0; j < height; j++) {
            bitmap[i][j] = 0x00;
        }
    }

}

/**
 * Copy constructor.
 *
 * @param orig
 */
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

/**
 * Destructor.
 */
BitmapObj::~BitmapObj() {
    for(qint32 i = 0; i < width / 8 + ( width % 8 == 0 ? 0 : 1 ); i++) {
        delete[] bitmap[i];
    }
    delete[] bitmap;

    delete qbitmap;
}

/**
 * Returns byte of 8 points in row. Be careful to not cross the bounds of bitmap
 * object.
 *
 * @param _x x-axes coordinates mesured form right top edge of matrix
 * @param _y y-axes coordinates mesured form right top edge of matrix
 * @return byte which represents 8 points in row
 */
quint8 BitmapObj::getByteGlobalCoordiantes(qint32 _x, qint32 _y) const {
    return bitmap[(_x - x) / 8][_y - y];
}

/**
 * Returns byte of 8 points in row. Be careful to not cross the bounds of bitmap
 * object.
 *
 * @param xDiv8 x-axes array coordinates (divide by 8) mesured form right top
 * edge of bitmap object
 * @param y y-axes coordinates mesured form right top edge of bitmap object
 * @return byte which represents 8 points in row
 */
quint8 BitmapObj::getByte(qint32 xDiv8, qint32 y) const {
    return bitmap[xDiv8][y];
}

/**
 * This funtion is cross-bounds save.
 *
 * @param x x-axes coordinates mesured form right top edge of bitmap object
 * @param y y-axes coordinates mesured form right top edge of bitmap object
 * @return logical value of point
 */
bool BitmapObj::getXY(qint32 x, qint32 y) const {
    if(x < 0 || y < 0 || x >= width || y >= height){
        return false;
    }
    return (bitmap[x / 8][y]) & (1 << x % 8);
}

/**
 * This funtion is cross-bounds save.
 *
 * @param _x x-axes coordinates mesured form right top edge of matrix
 * @param _y y-axes coordinates mesured form right top edge of matrix
 * @return logical value of point
 */
bool BitmapObj::getXYGlobalCoordiantes(qint32 _x, qint32 _y) const{
    return getXY(_x - x, _y - y);
}

/**
 * Sets byte to given value. Be careful to not cross the bounds of bitmap
 * object.
 *
 * @param xDiv8 x-axes array coordinates (divide by 8) mesured form right top
 * edge of bitmap object
 * @param y y-axes coordinates mesured form right top edge of bitmap object
 * @param val value to set
 */
void BitmapObj::setByte(qint32 xDiv8, qint32 y, quint8 val) {
    bitmap[xDiv8][y] = val;
}

/**
 * Sets point to given value. Be careful to not cross the bounds of bitmap
 * object.
 *
 * @param x x-axes coordinates mesured form right top edge of matrix
 * @param y y-axes coordinates mesured form right top edge of matrix
 * @param val
 */
void BitmapObj::setXY(qint32 x, qint32 y, bool val) {
    bitmap[x / 8][y] = val ? (bitmap[x / 8][y] | (1 << x % 8)) : (bitmap[x / 8][y] & ~(1 << x % 8));
}

/**
 * Sets point to given value. Be careful to not cross the bounds of bitmap
 * object.
 *
 * @param x x-axes coordinates mesured form right top edge of bitmap object
 * @param y y-axes coordinates mesured form right top edge of bitmap object
 * @param val
 */
void BitmapObj::setXYGlobalCoordiantes(qint32 _x, qint32 _y, bool val){
     setXY(_x - x, _y - y, val);
}

/**
 * Return QBitmap of the object for the view. For better performace is
 * the QBitmap constructed by the first call of this function and then stored.
 *
 * @return
 */
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
