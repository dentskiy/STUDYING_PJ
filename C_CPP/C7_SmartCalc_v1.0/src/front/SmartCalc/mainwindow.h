#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
extern "C" {
#include "../../backend/CCalc/s21_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_6_clicked();

  void on_pushButton_9_clicked();

  void on_pushButton_7_clicked();

  void on_pushButton_8_clicked();

  void on_pushButton_10_clicked();

  void on_pushButton_12_clicked();

  void on_pushButton_13_clicked();

  void on_pushButton_18_clicked();

  void on_pushButton_19_clicked();

  void on_pushButton_20_clicked();

  void on_pushButton_11_clicked();

  void on_pushButton_14_clicked();

  void on_pushButton_15_clicked();

  void on_pushButton_16_clicked();

  void on_pushButton_17_clicked();

  void on_pushButton_26_clicked();

  void on_pushButton_21_clicked();

  void on_pushButton_22_clicked();

  void on_pushButton_23_clicked();

  void on_pushButton_24_clicked();

  void on_pushButton_25_clicked();

  void on_pushButton_27_clicked();

  void on_pushButton_28_clicked();

  void on_pushButton_29_clicked();

  void on_pushButton_30_clicked();

  void on_pushButton_31_clicked();

  void on_pushButton_32_clicked();

  void on_pushButton_33_clicked();

  void on_checkBox_stateChanged(int arg1);

  void on_comboBox_2_currentIndexChanged(int index);

  void on_pushButton_34_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
