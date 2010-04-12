/* 
 * File:   Stone.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:35
 */

#include "Stone.h"

Stone::Stone(qint32 _x, qint32 _y, qint32 _width, qint32 _height) : BitmapObj(_x, _y, _width, _height) {
    color = QColor("darkGray");

    Q_ASSERT(_width % 8 == 0);

    for(qint32 i = 0; i < _width/8; i++){
        for (qint32 j = 0; j < _height; j++) {
            setByte(i, j, 0xFF);
        }
    }

}

