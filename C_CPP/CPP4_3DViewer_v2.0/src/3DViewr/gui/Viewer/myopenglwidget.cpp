#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  colorBack = QColor(0, 0, 0);
  colorDots = QColor(150, 0, 0);
  colorLine = QColor(250, 250, 250);
  controller = new s21::Faced;
  //  open_file(
  //      "/Users/elisabet/project/C_dir/C8_3DViewer_v1.0-1/src/code/back/cube.obj",
  //              &model_);
}

MyOpenGLWidget::~MyOpenGLWidget() { delete controller; }

void MyOpenGLWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,
                 static_cast<double>(width()) / static_cast<double>(height()),
                 1.0f, 100.0f);

  glColor3f(colorDots.redF(), colorDots.greenF(), colorDots.blueF());
  glColor3f(colorLine.redF(), colorLine.greenF(), colorLine.blueF());

  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0.0f, 0.0f, -5.0f);
}

void MyOpenGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void MyOpenGLWidget::paintGL() {
  glClearColor(colorBack.redF(), colorBack.greenF(), colorBack.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(colorLine.redF(), colorLine.greenF(), colorLine.blueF());

  lineAndDotsSettings();
  typeOfProjection();
  if (cmd) controller->executor(*cmd);
  delete cmd;
  cmd = nullptr;
  // Отрисовка линий
  glBegin(GL_LINES);
  size_t check = 0;
  if (controller->getModelFacesSize() != 0) {
  for (size_t i = 0; i < controller->getModelFacesSize() - 1; i++) {
  if (check != i && controller->getModelFaces(i) == controller->getModelFaces(check)) {
      i++;
      check = i;
  }

      size_t vertexIndex1 = controller->getModelFaces(i);
      size_t vertexIndex2 =controller->getModelFaces(i + 1);


        glVertex3f(controller->getModelX(vertexIndex1),
                   controller->getModelY(vertexIndex1),
                   controller->getModelZ(vertexIndex1));
        glVertex3f(controller->getModelX(vertexIndex2),
                   controller->getModelY(vertexIndex2),
                   controller->getModelZ(vertexIndex2));

  }
  }
  glEnd();

  // Отрисовка точек
  if (m_dotsType > 0) {
    glColor3f(colorDots.redF(), colorDots.greenF(), colorDots.blueF());
    glBegin(GL_POINTS);
    for (size_t i = 0; i < controller->getModelVertexSize(); i++) {
      glVertex3f(controller->getModelX(i), controller->getModelY(i),
                 controller->getModelZ(i));
    }
    glEnd();
  }

  drawVertexAndFaceCount();
}

void MyOpenGLWidget::drawVertexAndFaceCount() {
  QPainter painter(this);
  painter.setPen(QColor(255, 255, 255));  // Цвет текста (белый)
  painter.setFont(QFont("Arial", 12));    // Шрифт и размер
  int vertexCount = controller->getModelVertexSize();
  int faceCount = controller->getModelFacesSize();
  QString text =
      QString("Vertices: %1      Faces: %2").arg(vertexCount).arg(faceCount);

  painter.drawText(QPoint(10, 20), text);
}

void MyOpenGLWidget::lineAndDotsSettings() {
  glLineWidth(lineThickness);  // Устанавливаем ширину линий
  glPointSize(thicknessOfDots);  // Увеличиваем размер точек
  if (m_lineType) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(4, 0x00AA);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  if (m_dotsType == 2) {
    glDisable(GL_POINT_SMOOTH);
  } else if (m_dotsType == 1) {
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  }
}

void MyOpenGLWidget::typeOfProjection() {
  if (m_orthoProjection) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width() / height(), 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
  }
}

void MyOpenGLWidget::parseFile(QString *pathToFile) {
  pathToFileObj = pathToFile->toStdString();
  controller->setNewObject(pathToFileObj);
}

void MyOpenGLWidget::setMovingX(double value) {
  factory = new s21::LineMoveXFactory();
  cmd = factory->createCommand(value - save_.moveX);
  save_.moveX = value;
  delete factory;
  update();
}

void MyOpenGLWidget::setMovingY(double value) {
    factory = new s21::LineMoveYFactory();
    cmd = factory->createCommand(value - save_.moveY);
    save_.moveY = value;
    delete factory;
  update();
}

void MyOpenGLWidget::setMovingZ(double value) {
    factory = new s21::LineMoveZFactory();
    cmd = factory->createCommand(value - save_.moveZ);
    save_.moveZ = value;
    delete factory;
  update();
}

void MyOpenGLWidget::setRotationX(double value) {
    factory = new s21::CircularMoveXFactory();
    cmd = factory->createCommand(save_.rotateX - value);
  save_.rotateX = value;
  delete factory;
  update();
}

void MyOpenGLWidget::setRotationY(double value) {
    factory = new s21::CircularMoveYFactory();
    cmd = factory->createCommand(save_.rotateY - value);
  save_.rotateY = value;
  delete factory;
  update();
}

void MyOpenGLWidget::setRotationZ(double value) {
    factory = new s21::CircularMoveZFactory();
    cmd = factory->createCommand(save_.rotateZ - value);
  save_.rotateZ = value;
  delete factory;
  update();
}

void MyOpenGLWidget::setScale(double scale) {
  factory = new s21::ScaleMoveFactory;
  cmd = factory->createCommand(scale);
  delete factory;
  update();
}

void MyOpenGLWidget::setColorLine(QColor col) { colorLine = col; }

void MyOpenGLWidget::setColorDots(QColor col) { colorDots = col; }

void MyOpenGLWidget::setColorBack(QColor col) { colorBack = col; }

void MyOpenGLWidget::setThicknessOfDots(int value) {
  thicknessOfDots = (double)value / 8;
}

void MyOpenGLWidget::setLineThickness(int value) {
  lineThickness = (double)value / 5;
}

void MyOpenGLWidget::setMLineType(bool type) { m_lineType = type; }

void MyOpenGLWidget::setMDotsType(int type) { m_dotsType = type; }

void MyOpenGLWidget::setOrthoProjection(bool ortho) {
  m_orthoProjection = ortho;
}

void MyOpenGLWidget::resetSliders() {
   save_.moveX = 0.;
   save_.moveY = 0.;
   save_.moveZ = 0.;
   save_.rotateX = 0.;
   save_.rotateY = 0.;
   save_.rotateZ = 0.;


  update();
}
