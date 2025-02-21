#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

// убирает варнинги устаревшей версии кути
#define GL_SILENCE_DEPRECATION

#include <QtOpenGLWidgets/QOpenGLWidget>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#elif defined(__linux__)
#include <GL/gl.h>
#include <GL/glu.h>

#else
#error "Unsupported OS"
#endif

#include <QDebug>
#include <QFont>
#include <QFontMetrics>
#include <QOpenGLWidget>
#include <QPainter>

#include "../../back/Controller/Controller.h"

class MyOpenGLWidget : public QOpenGLWidget {
 public:
  MyOpenGLWidget(QWidget *parent = nullptr);
  ~MyOpenGLWidget();

  void setMovingX(double value);
  void setMovingY(double value);
  void setMovingZ(double value);
  void setRotationX(double value);
  void setRotationY(double value);
  void setRotationZ(double value);
  void setScale(double scale);

  void setColorLine(QColor col);
  void setColorDots(QColor col);
  void setColorBack(QColor col);
  void setThicknessOfDots(int value);
  void setLineThickness(int value);
  void setMLineType(bool type);
  void setMDotsType(int type);
  void setOrthoProjection(bool ortho);
  void resetSliders();
  void parseFile(QString *pathToFile);

  void drawVertexAndFaceCount();

  int getOrthoProjection() { return m_orthoProjection; }
  int getMLineType() { return m_lineType; }
  int getMDotsType() { return m_dotsType; }
  int getThicknessOfDots() { return thicknessOfDots; }
  int getLineThickness() { return lineThickness; }
  QColor getColorLine() { return colorLine; }
  QColor getColorDots() { return colorDots; }
  QColor getColorBack() { return colorBack; }

  std::string getPathOfFile() { return pathToFileObj; }

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  void lineAndDotsSettings();
  void typeOfProjection();
  void applyTransformations();

 private:
  QColor colorLine;
  QColor colorDots;
  QColor colorBack;
  bool m_lineType;
  int m_dotsType;
  bool m_orthoProjection;
  float thicknessOfDots;
  float lineThickness;

  struct slideSave {
      double moveX, moveY, moveZ;
      double rotateX, rotateY, rotateZ;

      slideSave() : moveX{}, moveY{}, moveZ{}, rotateX{}, rotateY{}, rotateZ{} {};
      ~slideSave() = default;
  };

  slideSave save_;

  s21::Faced* controller;
  s21::ICommandFactory* factory;
  s21::ModelCommand* cmd;

  std::string pathToFileObj;
};

#endif  // MYOPENGLWIDGET_H
