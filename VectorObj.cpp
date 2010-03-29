/* 
 * File:   VectorObj.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:35
 */

#include <qt4/QtGui/qimage.h>
#include <qt4/QtNetwork/qsslkey.h>

#include "VectorObj.h"

VectorObj::VectorObj() {
    vec = new QVector<QPair<quint32, quint32> >();
}

VectorObj::~VectorObj() {
    delete vec;
}

void VectorObj::addCoord(quint32 x, quint32 y) {
    vec->push_back(QPair<quint32,quint32>(x,y));
}

const QPair<quint32,quint32> VectorObj::getCoords(quint32 index) const {
    return vec->at(index);
}
