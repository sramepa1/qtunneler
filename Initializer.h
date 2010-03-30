/* 
 * File:   Validator.h
 * Author: pavel
 *
 * Created on 30. březen 2010, 11:18
 */

#ifndef _INITIALIZER_H
#define	_INITIALIZER_H

#include <QObject>
#include <QtCore>

#include "InitVector.h"

class Initializer : public QObject {

    Q_OBJECT

public:
    Initializer() {}
    virtual ~Initializer() {}

    void initGUI();
    QString initCore(bool create, quint32 port, QString host);

public slots:
    void validate(InitVector vec);

signals:
    void validated(QString message);

};

#endif	/* _INITIALIZER_H */

