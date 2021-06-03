#ifndef PIXELWIDGET_H
#define PIXELWIDGET_H

#include <QWidget>
#include<QPixmap>
class PixelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PixelWidget(QWidget *parent);
    void paintEvent(QPaintEvent*);
    void setPixmap(QPixmap pxm);
signals:
private:
    QPixmap pixmap;
};

#endif // PIXELWIDGET_H
