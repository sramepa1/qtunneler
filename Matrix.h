/* 
 * File:   Matrix.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:41
 */

#ifndef _MATRIX_H
#define	_MATRIX_H

#include "DefaultValues.h"
#include "BitmapObj.h"

class Matrix {
public:
    Matrix();
    virtual ~Matrix();

    virtual bool getXY(qint32 x, qint32 y) const { return (arr[x/8][y]) & (1 << (x%8)); }
    virtual quint8 getByte(qint32 xDiv8, qint32 y) const;

    virtual void setXY(qint32 x, qint32 y, bool val) { arr[x/8][y] = val ? (arr[x/8][y] | (1 << (x%8))) : (arr[x/8][y] & ~(1 << (x%8))); }
    virtual void setByte(qint32 xDiv8, qint32 y, quint8 val);

    virtual void reset();

    //Print given mask to matrix. (and)
    virtual void maskMatrix(const BitmapObj * mask);
    //Print given mask to matrix. (and not)
    virtual void invertMaskMatrix(const BitmapObj * mask);

protected:
    quint8** arr;
    // 1 represents clue, 0 represents tunnel

private:
    Matrix(const Matrix& orig) {} // disabled
};

#endif	/* _MATRIX_H */

