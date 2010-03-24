/* 
 * File:   Matrix.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:41
 */

#ifndef _MATRIX_H
#define	_MATRIX_H

#define DIMENSION (10*1024)

class Matrix {
public:
    Matrix();
    virtual ~Matrix();

    virtual bool getXY(quint32 x, quint32 y) const;
    virtual quint8 getByte(quint32 xDiv8, quint32 y) const;

    virtual void setXY(quint32 x, quint32 y, bool val);
    virtual void setByte(quint32 xDiv8, quint32 y, quint8 val);

    virtual void reset();

protected:
    quint8** arr;

private:
    Matrix(const Matrix& orig) {} // disabled
};

#endif	/* _MATRIX_H */

