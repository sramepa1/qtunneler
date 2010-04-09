/* 
 * File:   BaseWall.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:37
 */

#include "BaseWall.h"


BaseWall::BaseWall(quint32 _x, quint32 _y,quint32 _width, quint32 _heigth) : BitmapObj(_x, _y, _width, _heigth) {

    quint32 wDIV8 = width / 8;

    //Write border to bitmap
    for (int i = 0; i < 8; i++) {
        for (quint32 j = 0; j < wDIV8 / 3; j++) {
            setByte(j, i, 0xff);
        }

        for (quint32 j = wDIV8 / 3; j < (wDIV8 / 3) * 2; j++) {
            setByte(j, i, 0x00);
        }

        for (quint32 j = (wDIV8 / 3) * 2; j < wDIV8; j++) {
            setByte(j, i, 0xff);
        }
    }

    for (quint32 i = 8; i < height - 8; i++) {
        setByte(0, i, 0xff);
        for (quint32 j = 1; j < wDIV8 - 1; j++) {
            setByte(j, i, 0x00);
        }
        setByte(wDIV8 - 1, i, 0xff);
    }

    for (int i = height - 8; i < height; i++) {
        for (quint32 j = 0; j < wDIV8 / 3; j++) {
            setByte(j, i, 0xff);
        }

        for (quint32 j = wDIV8 / 3; j < (wDIV8 / 3) * 2; j++) {
            setByte(j, i, 0x00);
        }

        for (quint32 j = (wDIV8 / 3) * 2; j < wDIV8; j++) {
            setByte(j, i, 0xff);
        }
    }
    
}

