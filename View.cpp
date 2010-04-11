/* 
 * File:   View.cpp
 * Author: pavel
 * 
 * Created on 5. duben 2010, 10:51
 */

#include "View.h"

#include <QPalette>


View::View(QWidget* parent, Model* _model, Clicker* _clicker) : QWidget(parent), model(_model), clicker(_clicker) {
    tunnel.setColor(Qt::black);
    solid.setColor(Qt::gray);
    border.setColor(Qt::darkGray);
    shot.setColor(Qt::yellow);
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
    const uchar* data = model->getTunnelBitmapData(x,y,wid,hei);   
    painter.setPen(tunnel);
    painter.drawPixmap(0,0,QBitmap::fromData(QSize(wid,hei),data,QImage::Format_MonoLSB));
    delete[] data;

    // draw bitmap objects
    QVector<BitmapObj*> bitmaps = model->getSolidObjInRect(x,y,wid,hei);
    foreach(BitmapObj* bmp, bitmaps) {
        solid.setColor(bmp->getColor());
        painter.setPen(solid);
        painter.drawPixmap(bmp->getX1() - x, bmp->getY1() - y,*(bmp->getQBitmap()));
    }

    // draw border
    painter.setPen(Qt::NoPen);
    painter.setBrush(border);
    //TODO call model

    // draw shots
    QPoint view(x,y);
    painter.setBrush(shot);
    QVector<QPoint> shots = model->getShotsInRect(x,y,wid,hei);
    foreach(QPoint center, shots) {
        painter.drawEllipse(center - view,PROJECTILE_RADIUS,PROJECTILE_RADIUS);
    }
    

    //TODO draw tanks
}

void View::setViewpoint(qint32 _x, qint32 _y) {
    x = _x;
    y = _y;
}


void View::keyPressEvent(QKeyEvent* evt) {
    if(!clicker->keyPressEvent(evt)) QWidget::keyPressEvent(evt);
}

void View::keyReleaseEvent(QKeyEvent* evt) {
    if(!clicker->keyReleaseEvent(evt)) QWidget::keyReleaseEvent(evt);
}