#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QMessageBox>
#include<QColorDialog>
#include<QListWidget>
#include "pixeldialog.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new image_manager();
    this->buttonActive(false);
    this->ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setWindowTitle("Image Editor");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}


void MainWindow::on_pushButton_clicked()
{
    this->ui->listWidget->clear();
    this->manager->states.clear();

   QString text = this->ui->textEdit->toPlainText();
   QString fileName;
   if(text.length() == 0)
   {
        fileName  = QFileDialog::getOpenFileName(this,tr("Choisir une image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
   }else
   {
        fileName = text;
   }

   if(!this->manager->manage(fileName))
   {
       if(fileName.length())
       {

        QMessageBox::information(this,"Erreur de chargement de fichier","Le fichier \""+ fileName + "\" n'a pas réussi a être charger.");
       }
        this->buttonActive(false);
   }else
   {
        this->ui->textEdit->setText(fileName);
        this->updateImage();
        this->buttonActive(true);
        this->updateTotalColor();
   }
}

void MainWindow::updateTotalColor()
{
    QColor c = this->manager->getTotalColor();
    this->ui->label_2->setText("rouge: " + QString::number(c.red()) + "% vert: " +QString::number(c.green()) + "%  bleu: "+QString::number(c.blue())+"%");
}

void MainWindow::buttonActive(bool act)
{
    this->ui->pushButton_2->setEnabled(act);
    this->ui->pushButton_3->setEnabled(act);
    this->ui->pushButton_4->setEnabled(act);
    this->ui->pushButton_5->setEnabled(act);
    this->ui->pushButton_6->setEnabled(act);
    this->ui->pushButton_7->setEnabled(act);
    this->ui->pushButton_8->setEnabled(act);
    this->ui->pushButton_9->setEnabled(act);

    this->ui->horizontalSlider->setEnabled(act);
    this->ui->horizontalSlider_3->setEnabled(act);
    this->ui->horizontalSlider_4->setEnabled(act);
    this->ui->horizontalSlider_6->setEnabled(act);
    this->ui->horizontalSlider_5->setEnabled(act);
    this->ui->horizontalSlider_7->setEnabled(act);
}

void MainWindow::updateImage()
{
    QSize size;
    size.setWidth(ui->label->width());
    size.setHeight(ui->label->height());
    ui->label->setPixmap(this->manager->getPixmap(size));
    if(this->lastsize != this->manager->states.length())
    {
        this->lastsize = this->manager->states.length();
        this->ui->listWidget->addItem(QString::number(this->manager->states.length()-1));
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    this->manager->invert();
    this->updateTotalColor();
    this->updateImage();
}


void MainWindow::on_pushButton_6_clicked()
{
    int deg = (360* this->ui->horizontalSlider_3->value() )/100;
   this->manager->rotate(this->bruteMod,deg);
   this->updateImage();
}


void MainWindow::on_pushButton_5_clicked()
{
    QColor c = QColorDialog::getColor(Qt::white,this);
    int intensity = this->ui->horizontalSlider->value();

    this->manager->setFilter(c,intensity+1);
    this->updateImage();
}


void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    this->ui->label_4->setText(QString::number((360* value )/100)+"°  ");
}


void MainWindow::on_pushButton_2_clicked()
{
    this->manager->reverseV();
    this->updateImage();
}




void MainWindow::on_pushButton_3_clicked()
{
    this->manager->reverseH();
    this->updateImage();
}


void MainWindow::on_pushButton_7_clicked()
{
    this->manager->quality(this->bruteMod,this->ui->horizontalSlider_4->value());
    this->updateImage();
}


void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
     this->ui->label_5->setText(QString::number(value)+"%  ");
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(this->manager->states.length() != item->text().toInt())
    {
            this->manager->setindex_state(item->text().toInt());
            this->updateImage();
    }
}


void MainWindow::on_actionexporter_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer l'image"),QString(),tr("Images (*.png)"));
    if (!fileName.isEmpty())
    {
      this->manager->getPixmap().toImage().save(fileName,"PNG",this->saveQuality);
    }
}


void MainWindow::on_actionouvrir_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Confirmer l'ouverture d'une nouvelle image");
    msgBox.setInformativeText("Les modification apporter a l'image actuel ne seront pas sauvegarder.");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);

    if(msgBox.exec() == QMessageBox::Ok)
    {
    this->ui->textEdit->setText("");
    this->on_pushButton_clicked();
    }
}


void MainWindow::on_actionfermer_triggered()
{
    this->close();
}


void MainWindow::on_pushButton_8_clicked()
{
    QSize s;
    int w = this->manager->getImage().size().width()  * this->ui->horizontalSlider_5->value() /100;
     int h = this->manager->getImage().size().height()  * this->ui->horizontalSlider_6->value() /100;

    s.setWidth(w);
    s.setHeight(h);

    this->manager->resize(this->bruteMod,s);
    this->updateImage();
}


void MainWindow::on_horizontalSlider_7_valueChanged(int value)
{
    this->ui->label_8->setText(QString::number(100 - value)+"% ");
}


void MainWindow::on_pushButton_9_clicked()
{
    this->saveQuality = 100 - this->ui->horizontalSlider_7->value();
}


void MainWindow::on_radioButton_toggled(bool checked)
{
    this->bruteMod = !this->bruteMod;
}


void MainWindow::on_actionpixels_triggered()
{
    PixelDialog dpix = PixelDialog(this,this->manager->getPixmap());
    dpix.exec();
    QPixmap pixmap = this->manager->getPixmap();
    if(dpix.valide(&pixmap))
    {
       this->updateImage();
    }
}

