#ifndef PIXELWIDGET_H
#define PIXELWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QEvent>
#include <QKeyEvent>
class PixelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PixelWidget(QWidget *parent);
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent *) override;
    bool event(QEvent*) override;
    void setPixmap(QPixmap pxm);
    QPixmap getpixmap();
signals:
private:

    void drawgrid(QPainter& g);
    void drawcoord(QPainter& g);

    bool isPress = false;
    int scaleValue = 100;
    bool moveMod = true;
    bool lineAbove = false;
    bool ctrlPress = false;

    QPoint pos;
    QPoint start;
    QPixmap pixmap;
};

#endif // PIXELWIDGET_H
