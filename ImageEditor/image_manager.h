#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include<QImage>
#include<QPixmap>
#include<QVector>

class image_manager
{
public:
    image_manager();
    bool manage(QString);
    QImage getImage();
    QPixmap getPixmap();
    QPixmap getPixmap(QSize);

    QPixmap reverseH();
    QPixmap reverseV();
    QPixmap invert();

    QColor getTotalColor();
    void setFilter(QColor,int);

    QSize getSize();

    void resize(bool,QSize);
    void quality(bool,int);
    void rotate(bool,int);
    void scale(bool,int);

    QVector<QPixmap> states;
    void setindex_state(int);
private:
    void update();
    QImage current;
    QPixmap pixmap;
};

#endif // IMAGE_MANAGER_H
