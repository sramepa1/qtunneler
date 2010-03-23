/* 
 * File:   Matrix.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:41
 */

#ifndef _MATRIX_H
#define	_MATRIX_H

#define DIMENSION 10000

class Matrix {
public:
    Matrix();
    virtual ~Matrix();

    virtual bool getXY(int x, int y) const;
    virtual char getByte(int xDiv8, int y) const;

    virtual void setXY(int x, int y, bool val);
    virtual void setByte(int x, int y, char val);

    virtual void reset();

private:

    char** arr;

    Matrix(const Matrix& orig);
};

#endif	/* _MATRIX_H */

