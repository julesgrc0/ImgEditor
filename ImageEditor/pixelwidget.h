#ifndef PIXELWIDGET_H
#define PIXELWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QEvent>
class PixelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PixelWidget(QWidget *parent);
    void paintEvent(QPaintEvent*) override;
    bool event(QEvent*) override;
    void setPixmap(QPixmap pxm);

signals:
    void pixmapUpdate(QPixmap);
private:
    void drawgrid(QPainter& g);
    void drawcoord(QPainter& g);

    bool isPress = false;
    int scaleValue = 100;
    bool moveMod = true;
    bool lineAbove = false;

    QPoint pos;
    QPoint start;
    QPixmap pixmap;
};

#endif // PIXELWIDGET_H
