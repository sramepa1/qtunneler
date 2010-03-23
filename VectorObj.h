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
    
private:
    QVector<QPair<int, int> > vec;

    VectorObj(const VectorObj& orig);
};

#endif	/* _VECTOROBJ_H */

