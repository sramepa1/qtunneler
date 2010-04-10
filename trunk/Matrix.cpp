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
    for(qint32 i = 0; i < MATRIX_DIMENSION/8; i++) {
        arr[i] = new quint8[MATRIX_DIMENSION];
        for (qint32 j = 0; j < MATRIX_DIMENSION; j++) {
            setByte(i,j,0xFF);
        }
    }


    // for testing purposes <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    
    for(qint32 i = 0; i < MATRIX_DIMENSION/8; i++) {
        for (qint32 j = 128; j < 256; j++) {
            setByte(i,j,0);
        }
    }
    for(qint32 i = 16; i < 32; i++) {
        for (qint32 j = 0; j < MATRIX_DIMENSION; j++) {
            setByte(i,j,0);
        }
    }
    for(qint32 i = 0; i < MATRIX_DIMENSION; i++) {        
        setXY(i,i,false);
    }
    setXY(42,21,false);
    setXY(167,167,true);
    setXY(169,169,true);

    
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
            arr[x][y] = (quint8) 0;
        }
    }
}

void Matrix::setByte(qint32 xDiv8, qint32 y, quint8 val) {
    arr[xDiv8][y] = val;
}

// TODO more efficiently when byte-aligned !!!!!

void Matrix::maskMatrix(const BitmapObj * mask){
    int x = mask->getX1();
    int y = mask->getY1();
    for (int i = 0; i < mask->getWidth() && (i+x < MATRIX_DIMENSION); i++) {
        for (int j = 0; j < mask->getHeight() && (j+y < MATRIX_DIMENSION); j++) {
            if(getXY(x+i,y+j)) setXY(x+i,y+j,!mask->getXY(i,j));
        }
    }
}

void Matrix::invertMaskMatrix(const BitmapObj * mask){
    int x = mask->getX1();
    int y = mask->getY1();
    for (int i = 0; i < mask->getWidth() && (i+x < MATRIX_DIMENSION); i++) {
        for (int j = 0; j < mask->getHeight() && (j+y < MATRIX_DIMENSION); j++) {
            if(getXY(x+i,y+j)) setXY(x+i,y+j,(mask->getXY(i,j)));
        }
    }
}
