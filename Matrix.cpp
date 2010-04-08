/* 
 * File:   Matrix.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:41
 */

#include <QtCore>

#include "Matrix.h"


#include <iostream>

Matrix::Matrix() {
    arr = new quint8* [MATRIX_DIMENSION/8];
    for(quint32 i = 0; i < MATRIX_DIMENSION/8; i++) {
        arr[i] = new quint8[MATRIX_DIMENSION];
        for (quint32 j = 0; j < MATRIX_DIMENSION; j++) {
            setByte(i,j,0xFF);
        }
    }


    // for testing purposes <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    for(quint32 i = 0; i < MATRIX_DIMENSION/8; i++) {
        for (quint32 j = 128; j < 256; j++) {
            setByte(i,j,0);
        }
    }
    for(quint32 i = 16; i < 32; i++) {
        for (quint32 j = 0; j < MATRIX_DIMENSION; j++) {
            setByte(i,j,0);
        }
    }
    for(quint32 i = 0; i < MATRIX_DIMENSION; i++) {        
        setXY(i,i,false);
    }
    setXY(42,21,false);
    setXY(167,167,true);
    setXY(169,169,true);
}

Matrix::~Matrix() {
    for(quint32 i = 0; i < MATRIX_DIMENSION/8; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

quint8 Matrix::getByte(quint32 xDiv8, quint32 y) const {
    return arr[xDiv8][y];
}

void Matrix::reset() {
    for(quint32 x = 0; x < MATRIX_DIMENSION/8; x++) {
        for(quint32 y = 0; y < MATRIX_DIMENSION; y++) {
            arr[x][y] = (quint8) 0;
        }
    }
}

void Matrix::setByte(quint32 xDiv8, quint32 y, quint8 val) {
    arr[xDiv8][y] = val;
}

void Matrix::maskMatrix(BitmapObj mask){ //TODO check - probably bad implementation
    for (int i = mask.getX1(); i < mask.getWidth() / 8 && i < MATRIX_DIMENSION / 8; i++) {
        for (int j = mask.getY1(); j < mask.getHeight() && j < MATRIX_DIMENSION; j++) {
            arr[i][j] &= mask.getByte(i, j);
        }
    }

}