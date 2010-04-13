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

#ifndef _CLICKER_H
#define	_CLICKER_H

#include <QObject>
#include <QTime>
#include <QKeyEvent>

#include "Sender.h"
#include "DefaultValues.h"
#include "Model.h"

class Clicker : public QObject {

    Q_OBJECT

public:
    Clicker(QObject* parent = NULL, Model* _model = NULL);
    virtual ~Clicker();

    virtual void resetSender(Sender* s);

    // returns true when handled, false when not interested
    virtual bool keyPressEvent(QKeyEvent* evt);
    virtual bool keyReleaseEvent(QKeyEvent* evt);

public slots:

    // use sender to send confirmation packet
    virtual void confirmInitEnd();

    virtual void startClock();

protected:

    virtual void handleChange(uchar val, uchar* stored);

    virtual bool handleKey(QKeyEvent* evt, uchar val);

    uchar up;
    uchar down;
    uchar left;
    uchar right;

    uchar shoot;

    Sender* sender;
    QTime time;

    //not owner
    Model* model;

private:    
    Clicker(const Clicker& /*orig*/) : QObject() {} // disabled
};

#endif	/* _CLICKER_H */

