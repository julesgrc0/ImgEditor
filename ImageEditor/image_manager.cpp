#include "image_manager.h"
#include<QImage>
#include<QImageReader>

image_manager::image_manager()
{
}

QImage image_manager::getImage()
{
    return pixmap.toImage();
}

QPixmap image_manager::getPixmap(QSize s)
{
    return pixmap.scaled(s.width(),s.height(),Qt::AspectRatioMode::KeepAspectRatio);
}

QPixmap image_manager::getPixmap()
{
    return pixmap;
}

QSize image_manager::getSize()
{
    QSize s;
    s.setHeight(pixmap.width());
    s.setWidth(pixmap.height());
    return s;
}

QColor image_manager::getTotalColor()
{
    int r = 0,g = 0,b = 0;

    int w = current.width();
    int h = current.height();
    QColor act;

    for(int x = 0;x < w;x++)
    {
        for(int y=0;y< h;y++)
        {
            act = current.pixelColor(x,y);
            r += act.red();
            g += act.green();
            b += act.blue();
        }
    }

    QColor c;
    if(r && g && b)
    {
        int total = r+g+b;
        c.setRed(100*r/total);
        c.setGreen(100*g/total);
        c.setBlue(100*b/total);
    }

    return c;
}


void image_manager::setFilter(QColor color,int intensity)
{
    intensity = 100 - intensity;
    QImage tmp = current;
    QPoint p;
    QColor current_color;
      int color_r = 0,color_g = 0,color_b = 0;

    int w = tmp.width();
    int h = tmp.height();
    for(int x = 0;x < w;x++)
    {
        for(int y=0;y< h;y++)
        {
            p.setX(x);
            p.setY(y);
            current_color = current.pixelColor(x,y);

            color_r = (color.red() - ((color.red() * intensity) / 100));
            color_g = (color.green() - ((color.green() * intensity) / 100));
            color_b = (color.blue() - ((color.blue() * intensity) / 100));

            color_r = (current_color.red() + color_r)/2;
            color_g = (current_color.green() + color_g)/2;
            color_b = (current_color.blue() + color_b)/2;

            current_color.setRed(color_r);
            current_color.setGreen(color_g);
            current_color.setBlue(color_b);

            tmp.setPixelColor(p,current_color);
        }
    }

    current = tmp;
    this->update();
}

void image_manager::rotate(int deg)
{
    QTransform t;
    t.rotate(deg);
    current = this->current.transformed(t);
    this->update();
}

void image_manager::quality(int quality)
{
    quality = 100 - quality;
    current = this->current.scaled(quality,quality);
    this->update();
}

QPixmap image_manager::reverseV()
{
    /*
    QImage tmp = current;
    QPoint p;
    int w = tmp.width();
    int h = tmp.height();
    for(int x = 0;x < w;x++)
    {
        for(int y=0;y< h;y++)
        {
            p.setX(x);
            p.setY(y);
            tmp.setPixelColor(p,current.pixel(x,h-y));
        }
    }
    current = tmp;
    */
    this->current.mirror(false,true);
    this->update();
    return this->pixmap;
}

QPixmap image_manager::reverseH()
{
    /*
    QImage tmp = current;
    QPoint p;
    int w = tmp.width();
    int h = tmp.height();
    for(int x = 0;x < w;x++)
    {
        for(int y=0;y< h;y++)
        {
            p.setX(x);
            p.setY(y);
            tmp.setPixelColor(p,current.pixel(w-x,y));
        }
    }
    current = tmp;
    */
    this->current.mirror(true);
    this->update();
    return this->pixmap;
}

void image_manager::update()
{
    if(!this->current.isNull())
    {
        this->pixmap.convertFromImage(current);
        this->states.emplace_back(pixmap);
    }
}

void image_manager::setindex_state(int index)
{
        this->pixmap = this->states[index];
        this->current = this->pixmap.toImage();
        this->update();
}

QPixmap image_manager::invert()
{
    this->current.invertPixels();
    this->update();
    return this->pixmap;
}


bool image_manager::manage(QString image_path)
{
    QImageReader reader(image_path);
    this->current = reader.read();
    if(!this->current.isNull())
    {
        this->states.emplace_back(pixmap);
        this->update();
        return true;
    }
    return false;
}

