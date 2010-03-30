/* 
 * File:   Validator.h
 * Author: pavel
 *
 * Created on 30. březen 2010, 11:18
 */

#ifndef _VALIDATOR_H
#define	_VALIDATOR_H

#include <QObject>
#include <QtCore>

#include "InitVector.h"

class Validator : public QObject {

    Q_OBJECT

public:
    Validator() {}
    virtual ~Validator() {}

public slots:
    void validate(InitVector vec);

signals:
    void validated(QString message);

};

#endif	/* _VALIDATOR_H */

