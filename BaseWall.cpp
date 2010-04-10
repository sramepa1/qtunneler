/* 
 * File:   BaseWall.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:37
 */

#include "BaseWall.h"


BaseWall::BaseWall(qint32 _x, qint32 _y,qint32 _width, qint32 _heigth) : BitmapObj(_x, _y, _width, _heigth) {

    color = QColor("red"); // TODO change!!

    qint32 wDIV8 = width / 8;

    //Write border to bitmap
    for (int i = 0; i < 8; i++) {
        for (qint32 j = 0; j < wDIV8 / 3; j++) {
            setByte(j, i, 0xff);
        }

        for (qint32 j = wDIV8 / 3; j < (wDIV8 / 3) * 2; j++) {
            setByte(j, i, 0x00);
        }

        for (qint32 j = (wDIV8 / 3) * 2; j < wDIV8; j++) {
            setByte(j, i, 0xff);
        }
    }

    for (qint32 i = 8; i < height - 8; i++) {
        setByte(0, i, 0xff);
        for (qint32 j = 1; j < wDIV8 - 1; j++) {
            setByte(j, i, 0x00);
        }
        setByte(wDIV8 - 1, i, 0xff);
    }

    for (int i = height - 8; i < height; i++) {
        for (qint32 j = 0; j < wDIV8 / 3; j++) {
            setByte(j, i, 0xff);
        }

        for (qint32 j = wDIV8 / 3; j < (wDIV8 / 3) * 2; j++) {
            setByte(j, i, 0x00);
        }

        for (qint32 j = (wDIV8 / 3) * 2; j < wDIV8; j++) {
            setByte(j, i, 0xff);
        }
    }
    
}

