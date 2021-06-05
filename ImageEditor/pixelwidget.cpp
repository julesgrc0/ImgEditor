#include "pixelwidget.h"

#include<QPainter>
#include<QEvent>
#include<QMouseEvent>
#include<QWheelEvent>
#include<QContextMenuEvent>
#include<QMenu>

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

void PixelWidget::drawgrid(QPainter& g)
{
    QPointF p1;
    QPointF p2;
    int interval = this->width() /10;
    for(int x = -100;x < this->pixmap.width() + this->width();x+= interval)
    {
        for(int y = -100;y < this->pixmap.height() + this->height();y+= interval)
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
}

void PixelWidget::drawcoord(QPainter &g)
{
    int interval = this->width() /10;
    QPointF p;
    p.setX(interval);
    p.setY(interval-10);
    g.drawText(p,"("+QString::number(this->pos.x())+";"+QString::number(this->pos.y())+")");
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

        if(this->moveMod)
        {
            int x = ((start.x() - evt->x()));
            int y = ((start.y() - evt->y()));

            this->pos.setX(x);
            this->pos.setY(y);
        }else if(evt->x() <= this->width() && evt->y() <= this->height())
        {
            // scale bug (fix by reset scaleValue to default)
                this->scaleValue = 100;
            //

            int w = this->pixmap.width() *this->scaleValue/100;
            int h = this->pixmap.height() *this->scaleValue/100;

            if(evt->x() > this->pos.x() && evt->x() < this->pos.x() + w)
            {
                if(evt->y() > this->pos.y() && evt->y() < this->pos.y() + h)
                {
                    int x = evt->x() - this->pos.x();
                    int y = evt->y() - this->pos.y();

                    QImage tmpImg = this->pixmap.toImage();
                    tmpImg.setPixelColor(QPoint(x,y),Qt::black);

                    int drawSize = 1;
                    for(int k = -drawSize;k < drawSize;k++)
                    {
                        for(int j = -drawSize;j < drawSize;j++)
                        {
                            tmpImg.setPixelColor(QPoint(x+k,y+j),Qt::black);
                        }
                    }
                    this->pixmap.convertFromImage(tmpImg);

                    emit pixmapUpdate(this->pixmap);
                }
            }
        }

        this->repaint();
    }else if(e->type() == QEvent::Wheel)
    {
        int scrollSpeed = 1;
        QWheelEvent* evt = static_cast<QWheelEvent*>(e);
        if(evt->angleDelta().y() > 1)
        {
            this->scaleValue += scrollSpeed;
            //this->scaleValue > 100 ? this->scaleValue = 100 : 0;
        }else
        {
            this->scaleValue -= scrollSpeed;
            this->scaleValue < 0 ? this->scaleValue = 0 : 0;
        }
        this->repaint();
    }else if(e->type() == QEvent::ContextMenu)
    {
          QContextMenuEvent* evt = static_cast<QContextMenuEvent*>(e);

           QMenu menu;
           //menu.addAction(tr("couleurs"));
           menu.addAction(tr(!this->lineAbove ? "grilles dessus" : "grilles dessous"));

           this->pixmap.toImage().colorTable();



           QMenu* subMenuModes = menu.addMenu(tr("modes"));
           subMenuModes->addAction("dessin");
           subMenuModes->addAction("déplacement");

           QMenu* subMenuReset = menu.addMenu(tr("réinitialisation"));
           subMenuReset->addAction("zoom");
           subMenuReset->addAction("position");

           QAction*  selAct = menu.exec(evt->globalPos());
           if(selAct)
           {
               QString v = selAct->text();
                if(v == "zoom")
                {
                    this->scaleValue = 100;
                    this->repaint();
                }else if(v == "position")
                {
                    this->pos.setX(0);
                    this->pos.setY(0);

                    this->start.setX(0);
                    this->start.setY(0);
                    this->repaint();
                }else if(v == "dessin")
                {
                    this->moveMod = false;

                    // scale bug (fix by reset scaleValue to default)
                        this->scaleValue = 100;
                    //

                }else if(v == "déplacement")
                {
                    this->moveMod = true;
                }else if(v == "grilles dessus")
                {
                    this->lineAbove = true;
                     this->repaint();
                }else if(v == "grilles dessous")
                {
                     this->lineAbove = false;
                     this->repaint();
                }
           }
    }

    return QWidget::event(e);
}

void PixelWidget::paintEvent(QPaintEvent*)
{
    QPainter g = QPainter(this);
    QPen pen = QPen();
    pen.setColor(Qt::white);
    g.setPen(pen);

    g.fillRect(0,0,this->width(),this->height(),QColor(0,0,0,200));

    if(!this->lineAbove)
    {
        this->drawgrid(g);
        this->drawcoord(g);
    }

    QImage m =this->pixmap.scaled(this->pixmap.width() *this->scaleValue/100,this->pixmap.height()*this->scaleValue/100,Qt::KeepAspectRatio).toImage();
    g.drawImage(this->pos,m);

    if(this->lineAbove)
    {
        this->drawgrid(g);
        this->drawcoord(g);
    }
}
