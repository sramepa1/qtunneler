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

/**
 * Constructs the Matrix and fill it with true values (no tunels).
 */
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

/**
 * Resets the matrix to its initial state - fill it with true values (no tunels).
 */
void Matrix::reset() {
    for(qint32 x = 0; x < MATRIX_DIMENSION/8; x++) {
        for(qint32 y = 0; y < MATRIX_DIMENSION; y++) {
            arr[x][y] = (quint8) 0xff;
        }
    }
}

/**
 * Mask Matrix (logical and) with given @see BitmapObj.
 *
 * @param mask
 */
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

/**
 * Mask Matrix (logical and not) with given @see BitmapObj.
 *
 * @param mask
 */
void Matrix::invertMaskMatrix(const BitmapObj * mask){

    // copy-pasted code for performance reasons. This is called quite often...

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
