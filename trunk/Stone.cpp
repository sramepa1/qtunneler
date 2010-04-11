/* 
 * File:   Stone.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:35
 */

#include "Stone.h"
#include "Explosion.h"

Stone::Stone(qint32 _x, qint32 _y, qint32 _width, qint32 _heigth) : BitmapObj(_x, _y, _width, _heigth) {
    color = QColor("gray");

    for(qint32 i = 0; i < width; i++){
        for (qint32 j = 0; j < height; j++) {
            setXY(i, j, true);
        }
    }

}

Stone::~Stone() {
    
}

