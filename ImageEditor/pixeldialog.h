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
    bool valide(QPixmap *pixmap);

    ~PixelDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void pixmapUpdate(QPixmap pixmap);
private:
    Ui::PixelDialog *ui;
    bool stop = false;
    QPixmap pixmap;
};

#endif // PIXELDIALOG_H
