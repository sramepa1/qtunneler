/* 
 * File:   RoundObj.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:38
 */

#ifndef _ROUNDOBJ_H
#define	_ROUNDOBJ_H

class RoundObj {
public:
    qint32 x;
    qint32 y;
    
    RoundObj(quint8 c, quint32 i) : color(c),id(i) {}
    virtual ~RoundObj();

    virtual quint8 getColor() const {return color;}
    virtual quint32 getID() const {return id;}

protected:
    quint8 color;
    quint32 id;

private:
    RoundObj(const RoundObj& orig) {} // disabled
};

#endif	/* _ROUNDOBJ_H */

