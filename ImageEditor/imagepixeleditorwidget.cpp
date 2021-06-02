#include "imagepixeleditorwidget.h"
#include<QPainter>

ImagePixelEditorWidget::ImagePixelEditorWidget(QWidget *parent,QPixmap pixm) : QWidget(parent)
{
    this->pixmap = pixm;
}

void ImagePixelEditorWidget::paintEvent(QPaintEvent *event)
{
    /*QPainter g = QPainter(this);
    QRectF rect;
    rect.setHeight(this->height());
    rect.setWidth(this->width());
    g.drawImage(rect,this->pixmap.toImage());
    */
}



