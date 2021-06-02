#ifndef IMAGEPIXELEDITORWIDGET_H
#define IMAGEPIXELEDITORWIDGET_H

#include <QWidget>
#include<QPixmap>

class ImagePixelEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImagePixelEditorWidget(QWidget *parent,QPixmap);
protected:
    void paintEvent(QPaintEvent* event);
signals:
public slots:

private:
    QPixmap pixmap;
};

#endif // IMAGEPIXELEDITORWIDGET_H
