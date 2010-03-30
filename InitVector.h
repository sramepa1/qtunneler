/* 
 * File:   InitVector.h
 * Author: pavel
 *
 * Created on 30. březen 2010, 10:59
 */

#ifndef _INITVECTOR_H
#define	_INITVECTOR_H

#include <QtCore>

struct InitVector {

    InitVector(bool _create, QString _port, QString _host = "") : create(_create),host(_host),port(_port) {}

    QString host;
    QString port;
    bool create;

};

#endif	/* _INITVECTOR_H */

