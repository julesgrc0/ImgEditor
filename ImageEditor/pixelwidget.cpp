#include "pixelwidget.h"

#include<QPainter>

PixelWidget::PixelWidget(QWidget *parent) : QWidget(parent)
{
}

void PixelWidget::setPixmap(QPixmap pixm)
{
    this->pixmap = pixm;
}

void PixelWidget::paintEvent(QPaintEvent* e)
{
    QPainter g = QPainter(this);
    //QRect rect;
    //rect.setSize(this->size());
    //g.drawImage(rect,this->pixmap.toImage());

    QPoint p ;
    p.setX(0);
    p.setY(0);
    g.drawImage(p,this->pixmap.toImage());
}
