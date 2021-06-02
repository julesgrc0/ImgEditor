#include "pixeldialog.h"
#include "ui_pixeldialog.h"

PixelDialog::PixelDialog(QWidget *parent,QPixmap pixmap) :
    QDialog(parent),
    ui(new Ui::PixelDialog)
{
    ui->setupUi(this);
    this->ui->pushButton->setAutoDefault(false);
    this->ui->pushButton_2->setAutoDefault(true);
    this->pixmap = pixmap;
}

bool PixelDialog::valide(QPixmap *pixmap)
{
    (*pixmap) = this->pixmap;
    return this->stop;
}

PixelDialog::~PixelDialog()
{
    delete ui;
}

void PixelDialog::on_pushButton_2_clicked()
{
    this->stop = true;
    this->close();
}


void PixelDialog::on_pushButton_clicked()
{
    this->stop = false;
    this->close();
}

