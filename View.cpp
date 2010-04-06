/* 
 * File:   View.cpp
 * Author: pavel
 * 
 * Created on 5. duben 2010, 10:51
 */

#include "View.h"

#include <QPalette>

#include <iostream>

View::View(QWidget* parent, Model* _model) : QWidget(parent), model(_model) {

    setAutoFillBackground(true);

    background.setColor(Qt::black);
    background.setStyle(Qt::SolidPattern);

    QPalette p (palette());
    p.setColor(QPalette::Window,Qt::black);
    setPalette(p);

    texture.setColor(Qt::black);

    tile = QPixmap::fromImage(QImage("dirt_small.png"));
}

View::~View() {
}

void View::paintEvent(QPaintEvent* /*evt*/) {

    QPainter painter(this);
    //painter.setBackgroundMode(Qt::OpaqueMode);
    //painter.setBackground(background);
    painter.setPen(Qt::NoPen);

    painter.drawTiledPixmap(0,0,width(),height(),tile,width()%318,height()%288);

    const uchar* data = model->getBitmapData(0,0,width(),height());
    texture.setTexture(QBitmap::fromData(QSize(width(),height()),data,QImage::Format_MonoLSB));    

    painter.setBrush(texture);
    painter.drawRect(0,0,width()-1,height()-1);

    
    delete data;

}

