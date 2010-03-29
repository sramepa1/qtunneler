/* 
 * File:   Matrix.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:41
 */

#include "Matrix.h"

Matrix::Matrix() {
    arr = new quint8* [DIMENSION/8];
    for(quint32 i = 0; i < DIMENSION/8; i++) {
        arr[i] = new quint8[DIMENSION];
        for (quint32 j = 0; j < DIMENSION; j++) {
            setByte(i,j,0xFF);
        }
    }
}

Matrix::~Matrix() {
    for(quint32 i = 0; i < DIMENSION/8; i++) {
        delete arr[i];
    }
    delete arr;
}

quint8 Matrix::getByte(qint32 xDiv8, qint32 y) const {
    return arr[xDiv8][y];
}

bool Matrix::getXY(quint32 x, quint32 y) const {
    return ((arr[x/8][y]) & (1 << x%8) != 0);
}

void Matrix::reset() {
    for(quint32 x = 0; x < DIMENSION/8; x++) {
        for(quint32 y = 0; y < DIMENSION; y++) {
            arr[x][y] = (quint8) 0;
        }
    }
}

void Matrix::setByte(quint32 xDiv8, quint32 y, quint8 val) {
    arr[xDiv8][y] = val;
}

void Matrix::setXY(quint32 x, quint32 y, bool val) {
    arr[x/8][y] = val ? (arr[x/8][y] | (1 << x%8)) : (arr[x/8][y] & (1 << x%8));
}