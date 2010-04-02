/* 
 * File:   VectorObj.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:35
 */

#ifndef _VECTOROBJ_H
#define	_VECTOROBJ_H

#include <QtCore>
#include "DefaultValues.h"

class VectorObj {
public:
    VectorObj();
    virtual ~VectorObj();
    
    virtual void addCoord(quint32 x, quint32 y);
    
    virtual const QPair<quint32,quint32> getCoords(quint32 index) const;
    virtual quint32 getCoordCount() const {return vec->size();}

    // TODO iterator method? (return Qt const_iterator?)

    // TODO abstract drawYourself method (or something similar)
    
protected:
    QVector<QPair<quint32, quint32> > * vec;

private:
    VectorObj(const VectorObj& orig) {} // disabled
};

#endif	/* _VECTOROBJ_H */

