#include "mementopatrn.h"

void SettingsMemenro::saveInitSettings() {
  QSettings viewerSettings(
      QCoreApplication::applicationDirPath() + "settingsViews.ini",
      QSettings::IniFormat);

  viewerSettings.setValue("ColorBack", back);
  viewerSettings.setValue("ColorDots", dots);
  viewerSettings.setValue("ColorLine", line);
  viewerSettings.setValue("TypeLine", typeLine);
  viewerSettings.setValue("TypeDots", typeDots);
  viewerSettings.setValue("TypeProjection", typePjoction);
  viewerSettings.setValue("LineThickness", lineThickness);
  viewerSettings.setValue("DotsThickness", dotsThickness);
  viewerSettings.setValue("PathOfFile", path);

  viewerSettings.setValue("ScrolMoveX", moveX);
  viewerSettings.setValue("ScrolMoveY", moveY);
  viewerSettings.setValue("ScrolMoveZ", moveZ);
  viewerSettings.setValue("ScrolRotateX", rotateX);
  viewerSettings.setValue("ScrolRotateY", rotateY);
  viewerSettings.setValue("ScrolRotateZ", rotateZ);
  viewerSettings.setValue("ScrolScale", scale);
  viewerSettings.setValue("BMP", bmp);
  viewerSettings.setValue("JPEG", jpeg);
}

void SettingsMemenro::setSettingsOpenGLWidget(MyOpenGLWidget *openGLWidget) {
  back = openGLWidget->getColorBack();
  dots = openGLWidget->getColorDots();
  line = openGLWidget->getColorLine();
  typeLine = openGLWidget->getMLineType();
  typeDots = openGLWidget->getMDotsType();
  typePjoction = openGLWidget->getOrthoProjection();
  path = QString::fromStdString(openGLWidget->getPathOfFile());
  qDebug() << "saveSettings";
}

void SettingsMemenro::setMainWindowScrollMove(int x, int y, int z) {
  moveX = x;
  moveY = y;
  moveZ = z;
}

void SettingsMemenro::setMainWindowScrollRotate(int x, int y, int z) {
  rotateX = x;
  rotateY = y;
  rotateZ = z;
}

void SettingsMemenro::setMainWindowScrollScale(int dotsScroll,
                                               int lineScroll) {
  dotsThickness = dotsScroll;
  lineThickness = lineScroll;
}

void SettingsMemenro::setMainWindowRadioButton(int rbbmp, int rbjpeg) {
  bmp = rbbmp;
  jpeg = rbjpeg;
}

void SettingsMemenro::settingViewer(MyOpenGLWidget *openGLWidget) {
  QSettings viewerSettings(
      QCoreApplication::applicationDirPath() + "settingsViews.ini",
      QSettings::IniFormat);

  back = viewerSettings.value("ColorBack", QColor(0, 0, 0)).value<QColor>();
  openGLWidget->setColorBack(back);
  dots = viewerSettings.value("ColorDots", QColor(150, 0, 0)).value<QColor>();
  openGLWidget->setColorDots(dots);
  line =
      viewerSettings.value("ColorLine", QColor(250, 250, 250)).value<QColor>();
  openGLWidget->setColorLine(line);
  typeLine = viewerSettings.value("TypeLine", 0).toInt();
  openGLWidget->setMLineType(typeLine);
  typeDots = viewerSettings.value("TypeDots", 0).toInt();
  openGLWidget->setMDotsType(typeDots);
  typePjoction = viewerSettings.value("TypeProjection", 1).toInt();
  openGLWidget->setOrthoProjection(typePjoction);
  path = viewerSettings.value("PathOfFile", "default_value").toString();
  openGLWidget->parseFile(&path);
  lineThickness = viewerSettings.value("LineThickness", 1).toInt();
  dotsThickness = viewerSettings.value("DotsThickness", 10.0).toInt();
  moveX = viewerSettings.value("ScrolMoveX", 0).toInt();
  moveY = viewerSettings.value("ScrolMoveY", 0).toInt();
  moveZ = viewerSettings.value("ScrolMoveZ", 0).toInt();
  rotateX = viewerSettings.value("ScrolRotateX", 0).toInt();
  rotateY = viewerSettings.value("ScrolRotateY", 0).toInt();
  rotateZ = viewerSettings.value("ScrolRotateZ", 0).toInt();
  scale = viewerSettings.value("ScrolScale", 100).toInt();
  bmp = viewerSettings.value("BMP", 1).toInt();
  jpeg = viewerSettings.value("JPEG", 0).toInt();

  qDebug() << "settings";
}

void Caretaker::saveSettings() { memento_.saveInitSettings(); }

void Caretaker::settingsOpenGLWidget(MyOpenGLWidget *openGLWidget) {
  memento_.setSettingsOpenGLWidget(openGLWidget);
}

void Caretaker::mainWindowScrollMove(int x, int y, int z) {
  memento_.setMainWindowScrollMove(x, y, z);
}

void Caretaker::mainWindowScrollRotate(int x, int y, int z) {
  memento_.setMainWindowScrollRotate(x, y, z);
}

void Caretaker::mainWindowScrollScale(int dotsScroll,
                                      int lineScroll) {
  memento_.setMainWindowScrollScale(dotsScroll, lineScroll);
}

void Caretaker::mainWindowRadioButton(int rbbmp, int rbjpeg) {
  memento_.setMainWindowRadioButton(rbbmp, rbjpeg);
}
