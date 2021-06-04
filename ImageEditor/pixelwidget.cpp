#include "pixelwidget.h"

#include<QPainter>
#include<QEvent>
#include<QMouseEvent>

PixelWidget::PixelWidget(QWidget *parent) : QWidget(parent)
{
    this->pos.setX(0);
    this->pos.setY(0);

    this->start.setX(0);
    this->start.setY(0);
}

void PixelWidget::setPixmap(QPixmap pixm)
{
    this->pixmap = pixm;
}


bool PixelWidget::event(QEvent *e)
{

    if(e->type() == QEvent::MouseButtonPress)
    {
        this->isPress = true;
        QMouseEvent* evt = static_cast<QMouseEvent*>(e);
        this->start.setX(this->pos.x() + evt->x());
        this->start.setY(this->pos.y() +evt->y());
    }
    else if(e->type() == QEvent::MouseButtonRelease)
    {
        this->isPress = false;
    }
    else if(e->type() == QEvent::MouseMove && this->isPress)
    {
            QMouseEvent* evt = static_cast<QMouseEvent*>(e);

            int x = ((start.x() - evt->x()));
            int y = ((start.y() - evt->y()));

            this->pos.setX(x);
            this->pos.setY(y);

            this->repaint();
    }

    return QWidget::event(e);
}

void PixelWidget::paintEvent(QPaintEvent*)
{
    QPainter g = QPainter(this);
    QPen pen = QPen();
    QPointF p1;
    QPointF p2;

    pen.setColor(Qt::white);
    g.setPen(pen);

    g.fillRect(0,0,this->width(),this->height(),QColor(0,0,0,150));

    for(int x = -100;x < this->pixmap.width() + 100;x+= 50)
    {
        for(int y = -100;y < this->pixmap.height() + 100;y+= 50)
        {
             p1.setX(x);
             p1.setY(-100);

             p2.setX(x);
             p2.setY(y);

             g.drawLine(p1,p2);

             p1.setX(-100);
             p1.setY(y);

             p2.setX(x);
             p2.setY(y);

             g.drawLine(p1,p2);
        }
    }

    //this->pixmap.scaled(,Qt::KeepAspectRatio);

    g.drawImage(this->pos,this->pixmap.toImage());
}
