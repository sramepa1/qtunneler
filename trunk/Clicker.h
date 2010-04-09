/* 
 * File:   Clicker.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:43
 */

#ifndef _CLICKER_H
#define	_CLICKER_H

#include <QObject>

#include "Sender.h"

class Clicker : public QObject {

    Q_OBJECT

public:
    Clicker(QObject* parent = NULL);
    virtual ~Clicker();

    virtual void resetSender(Sender* s);

protected:

    Sender* sender;

private:    
    Clicker(const Clicker& orig) {} // disabled
};

#endif	/* _CLICKER_H */

