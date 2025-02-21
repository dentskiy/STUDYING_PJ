#ifndef MEMENTOPATRN_H
#define MEMENTOPATRN_H
#include <QCoreApplication>
#include <QDebug>
#include <QMainWindow>
#include <QSettings>
#include <QSlider>

#include "myopenglwidget.h"

namespace Ui {
class MainWindow;
}

class SettingsMemenro {
  friend class MainWindow;

 public:
  void saveInitSettings();

  void setSettingsOpenGLWidget(MyOpenGLWidget *openGLWidget);
  void setMainWindowScrollMove(int x, int y, int z);
  void setMainWindowScrollRotate(int x, int y, int z);
  void setMainWindowScrollScale(int dotsScroll,
                                int lineScroll);
  void setMainWindowRadioButton(int rbbmp, int rbjpeg);

 private:
  QString path;
  int typeLine;
  int typeDots;
  int typePjoction;
  QColor dots;
  QColor line;
  QColor back;
  int lineThickness;
  int dotsThickness;
  int typeImage;
  int moveX;
  int moveY;
  int moveZ;
  int rotateX;
  int rotateY;
  int rotateZ;
  int scale;
  int bmp;
  int jpeg;

  void settingViewer(MyOpenGLWidget *openGLWidget);
};

class Caretaker {
 public:
  void saveSettings();
  void settingsOpenGLWidget(MyOpenGLWidget *openGLWidget);
  void mainWindowScrollMove(int x, int y, int z);
  void mainWindowScrollRotate(int x, int y, int z);
  void mainWindowScrollScale(int dotsScroll, int lineScroll);
  void mainWindowRadioButton(int rbbmp, int rbjpeg);

 private:
  SettingsMemenro memento_;
};

#endif  // MEMENTO_H
