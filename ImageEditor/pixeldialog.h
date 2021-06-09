#ifndef PIXELDIALOG_H
#define PIXELDIALOG_H

#include <QDialog>
#include<QPixmap>

namespace Ui {
class PixelDialog;
}

class PixelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PixelDialog(QWidget *parent,QPixmap pixmap);
    bool valide(QPixmap *pix);

    ~PixelDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::PixelDialog *ui;
    QColor pen_color;
    bool stop = false;
    QPixmap pixmap;
    int pen_size = 1;
};

#endif // PIXELDIALOG_H
