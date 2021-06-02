#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QListWidget>
#include "image_manager.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_horizontalSlider_3_valueChanged(int value);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_horizontalSlider_4_valueChanged(int value);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_actionexporter_triggered();

    void on_actionouvrir_triggered();

    void on_actionfermer_triggered();

    void on_pushButton_8_clicked();

    void on_horizontalSlider_7_valueChanged(int value);

    void on_pushButton_9_clicked();

    void on_radioButton_toggled(bool checked);

private:
    bool bruteMod = false;
    void buttonActive(bool);
    void updateImage();
    void updateTotalColor();
    int saveQuality = 100;
    image_manager* manager;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
