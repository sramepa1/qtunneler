/* 
 * File:   View.cpp
 * Author: pavel
 * 
 * Created on 5. duben 2010, 10:51
 */

#include "View.h"

#include "OrientedRoundObj.h"

View::View(QWidget* parent, Model* _model, Clicker* _clicker) : QWidget(parent), model(_model), clicker(_clicker) {
    tunnel.setColor(Qt::black);
    solid.setColor(Qt::gray);
    border.setColor(Qt::darkGray);
    border.setStyle(Qt::SolidPattern);
    shot.setColor(Qt::yellow);
    tile = QPixmap::fromImage(QImage(":/tile.png"));
    x = y = 0;

    int playerIDs[3] = {RED_PLAYER, GREEN_PLAYER, BLUE_PLAYER};
    QString strings[3] = {"red", "green", "blue"};
    for (int i = 0; i < 3; i++) {
        QString prefix = QString(":/tanks/") + strings[i];
        tanks[playerIDs[i]][OrientedRoundObj::NORTH] =      QPixmap::fromImage(QImage(prefix + QString("-N.png")));
        tanks[playerIDs[i]][OrientedRoundObj::NORTH_EAST] = QPixmap::fromImage(QImage(prefix + QString("-NE.png")));
        tanks[playerIDs[i]][OrientedRoundObj::EAST] =       QPixmap::fromImage(QImage(prefix + QString("-E.png")));
        tanks[playerIDs[i]][OrientedRoundObj::SOUTH_EAST] = QPixmap::fromImage(QImage(prefix + QString("-SE.png")));
        tanks[playerIDs[i]][OrientedRoundObj::SOUTH] =      QPixmap::fromImage(QImage(prefix + QString("-S.png")));
        tanks[playerIDs[i]][OrientedRoundObj::SOUTH_WEST] = QPixmap::fromImage(QImage(prefix + QString("-SW.png")));
        tanks[playerIDs[i]][OrientedRoundObj::WEST] =       QPixmap::fromImage(QImage(prefix + QString("-W.png")));
        tanks[playerIDs[i]][OrientedRoundObj::NORTH_WEST] = QPixmap::fromImage(QImage(prefix + QString("-NW.png")));
    }

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

    model->containerAccess.lock();

    // draw tunnel network
    const uchar* data = model->getTunnelBitmapData(x,y,wid,hei);   
    painter.setPen(tunnel);
    painter.drawPixmap(0,0,QBitmap::fromData(QSize(wid,hei),data,QImage::Format_MonoLSB));
    delete[] data;

    // draw border
    painter.setPen(Qt::NoPen);
    painter.setBrush(border);
    QVector<QRect> borders = model->getBorderInRect(x,y,wid,hei);
    foreach(QRect r, borders) {
        painter.drawRect(r.x() - x, r.y() - y, r.width(), r.height());
    }

    // draw bitmap objects
    QVector<BitmapObj*> bitmaps = model->getSolidObjInRect(x,y,wid,hei);
    foreach(BitmapObj* bmp, bitmaps) {
        solid.setColor(bmp->getColor());
        painter.setPen(solid);
        painter.drawPixmap(bmp->getX1() - x, bmp->getY1() - y,*(bmp->getQBitmap()));
    }

    // draw projectiles
    painter.setPen(Qt::NoPen);
    QPoint view(x,y);
    painter.setBrush(shot);
    QVector<QPoint> shots = model->getShotsInRect(x,y,wid,hei);
    foreach(QPoint center, shots) {
        painter.drawEllipse(center - view,PROJECTILE_RADIUS,PROJECTILE_RADIUS);
    }

    // draw tanks
    painter.setBrush(Qt::NoBrush);
    QVector<OrientedRoundObj*> tankVec = model->getTanksInRect(x,y,wid,hei);
    foreach(OrientedRoundObj* tank, tankVec) {
        painter.drawPixmap(tank->getX1() - x,tank->getY1() - y,tanks[tank->id][tank->rotation]);
    }

    model->containerAccess.unlock();
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