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
    tunnel.setColor(Qt::black);
    solid.setColor(Qt::gray);
    shot.setColor(Qt::red);
    tile = QPixmap::fromImage(QImage(":/tile.png"));
    x = y = 0;
}

View::~View() {
}

void View::paintEvent(QPaintEvent* /*evt*/) {

    int wid = width();
    int hei = height();

    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    // draw background
    painter.drawTiledPixmap(0,0,width(),height(),tile, x % tile.width(), y % tile.height());

    // draw tunnel network
    const uchar* data = model->getTunnelBitmapData(0,0,wid,hei);
    tunnel.setTexture(QBitmap::fromData(QSize(wid,hei),data,QImage::Format_MonoLSB));
    delete data;
    painter.setBrush(tunnel);
    painter.drawRect(0,0,wid,hei);

    // draw bitmap objects
    QVector<BitmapObj*> bitmaps = model->getSolidObjInRect(x,y,wid,hei);
    foreach(BitmapObj* bmp, bitmaps) {
        solid.setColor(bmp->getColor());        
        solid.setTexture(*(bmp->getQBitmap()));
        painter.setBrush(solid);
        painter.drawRect(bmp->getX1() - x, bmp->getY1() - y, bmp->getWidth(), bmp->getHeight());
    }

    // draw shots
    QPoint view(x,y);
    painter.setBrush(shot);
    QVector<QPoint> shots = model->getShotsInRect(x,y,wid,hei);
    foreach(QPoint center, shots) {
        painter.drawEllipse(center - view,PROJECTILE_RADIUS,PROJECTILE_RADIUS);
    }
    

    //TODO draw tanks
}

QPoint View::getViewpoint() {
    return QPoint(x,y);
}


void View::setViewpoint(quint32 _x, quint32 _y) {
    x = _x;
    y = _y;
}

void View::paintBitmap(QPainter& painter, BitmapObj* obj) {

    //TODO

}
