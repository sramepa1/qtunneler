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
    
    virtual void addCoord(int x, int y);
    
    virtual const QPair<int,int>* const getCoords(int index) const;
    virtual size_t getCoordCount() const {return vec.size();}
    
protected:
    QVector<QPair<int, int> > vec;

private:
    VectorObj(const VectorObj& orig) {} // disabled
};

#endif	/* _VECTOROBJ_H */

