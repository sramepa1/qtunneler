/* 
 * File:   VectorObj.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:35
 */

#ifndef _VECTOROBJ_H
#define	_VECTOROBJ_H

#include <QtCore>

class VectorObj {
public:
    VectorObj();
    virtual ~VectorObj();
    
    virtual void addCoord(qint32 x, qint32 y);
    
    virtual const QPair<qint32,qint32>* const getCoords(qint32 index) const;
    virtual quint32 getCoordCount() const {return vec.size();}

    // TODO abstract drawYourself method (or something similar)
    
protected:
    QVector<QPair<qint32, qint32> > vec;

private:
    VectorObj(const VectorObj& orig) {} // disabled
};

#endif	/* _VECTOROBJ_H */

