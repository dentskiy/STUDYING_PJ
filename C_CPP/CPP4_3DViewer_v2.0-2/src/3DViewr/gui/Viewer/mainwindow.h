#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>

#include "gifmove.h"
#include "mementopatrn.h"
#include "myopenglwidget.h"
#include "ui_mainwindow.h"

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
  void FileProcessing(QString file_path);
  void on_scrollMoveX_valueChanged(int value);
  void on_buttonColorDots_clicked();
  void on_scrollBarThicknessDots_valueChanged(int value);
  void on_buttonColorLine_clicked();
  void on_scrollBarThicknessLine_valueChanged(int value);
  void on_boxTypeLine_activated(int index);
  void on_boxTypeDots_activated(int index);
  void on_buttonColorBack_clicked();
  void on_boxTypeProjection_activated(int index);
  void on_scrollMoveY_valueChanged(int value);
  void on_scrollMoveZ_valueChanged(int value);
  void on_scrollRotationX_valueChanged(int value);
  void on_scrollRotationY_valueChanged(int value);
  void on_scrollRotationZ_valueChanged(int value);
  void resetScrolls();
  void on_buttonScreen_clicked();
  void on_buttonGif_clicked();

  void saveSettings();
  void loadSetting();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

private:
 private:
  Ui::MainWindow *ui;
  MyOpenGLWidget *openGLWidget;
};
#endif  // MAINWINDOW_H
