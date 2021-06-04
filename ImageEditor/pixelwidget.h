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
private:

    bool isPress = false;
    QPoint pos;
    QPoint start;
    QPixmap pixmap;
};

#endif // PIXELWIDGET_H
