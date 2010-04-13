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

#include <QtCore>

#include "Matrix.h"


#include <iostream>

Matrix::Matrix() {
    arr = new quint8* [MATRIX_DIMENSION/8];
    for(qint32 i = 0; i < MATRIX_DIMENSION/8; i++) {
        arr[i] = new quint8[MATRIX_DIMENSION];
        for (qint32 j = 0; j < MATRIX_DIMENSION; j++) {
            setByte(i,j,0xFF);
        }
    }  
}

Matrix::~Matrix() {
    for(qint32 i = 0; i < MATRIX_DIMENSION/8; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

quint8 Matrix::getByte(qint32 xDiv8, qint32 y) const {
    return arr[xDiv8][y];
}

void Matrix::reset() {
    for(qint32 x = 0; x < MATRIX_DIMENSION/8; x++) {
        for(qint32 y = 0; y < MATRIX_DIMENSION; y++) {
            arr[x][y] = (quint8) 0xff;
        }
    }
}

void Matrix::setByte(qint32 xDiv8, qint32 y, quint8 val) {
    arr[xDiv8][y] = val;
}


// copy-pasted code for performance reasons. This is called quite often...

void Matrix::maskMatrix(const BitmapObj * mask){
    int x = mask->getX1();
    int y = mask->getY1();
    int wid = mask->getWidth();
    int hei = mask->getHeight();

    if(x%8 == 0) { // byte-aligned

        x /= 8;
        wid = wid%8 == 0 ? wid/8 : wid/8 + 1;
        
        for (int i = 0; i < wid && (i+x < MATRIX_DIMENSION/8); i++) {
            for (int j = 0; j < hei && (j+y < MATRIX_DIMENSION); j++) {
                setByte(x+i,y+j, getByte(x+i,y+j) & mask->getByte(i,j));
            }
        }

    }else { // not byte-aligned

        for (int i = 0; i < wid && (i+x < MATRIX_DIMENSION); i++) {
            for (int j = 0; j < hei && (j+y < MATRIX_DIMENSION); j++) {
                if(getXY(x+i,y+j)) setXY(x+i,y+j, mask->getXY(i,j) );
            }
        }
    }
}

void Matrix::invertMaskMatrix(const BitmapObj * mask){
    int x = mask->getX1();
    int y = mask->getY1();
    int wid = mask->getWidth();
    int hei = mask->getHeight();

    if(x%8 == 0) { // byte-aligned

        x /= 8;
        wid = (wid%8 == 0) ? (wid/8) : (wid/8 + 1);

        for (int i = 0; i < wid && (i+x < MATRIX_DIMENSION/8); i++) {
            for (int j = 0; j < hei && (j+y < MATRIX_DIMENSION); j++) {
                setByte(x+i,y+j, getByte(x+i,y+j) & ~(mask->getByte(i,j)));
            }
        }

    }else { // not byte-aligned

        for (int i = 0; i < wid && (i+x < MATRIX_DIMENSION); i++) {
            for (int j = 0; j < hei && (j+y < MATRIX_DIMENSION); j++) {
                if(getXY(x+i,y+j)) setXY(x+i,y+j, !(mask->getXY(i,j)) );
            }
        }
    }
}
