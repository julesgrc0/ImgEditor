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
    this->ui->widget->setPixmap(this->pixmap);
    this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
}


bool PixelDialog::valide(QPixmap *pix)
{
    (*pix) = this->pixmap;
    return this->stop;
}

PixelDialog::~PixelDialog()
{
    delete ui;
}

void PixelDialog::on_pushButton_2_clicked()
{
    this->pixmap = this->ui->widget->getpixmap();
    this->stop = true;
    this->close();
}


void PixelDialog::on_pushButton_clicked()
{
    this->stop = false;
    this->close();
}

