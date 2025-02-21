#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(1152, 720);
  setWindowTitle("3DViewer_v1.0");
  openGLWidget = new MyOpenGLWidget(this);
  openGLWidget->setGeometry(0, 0, 950, 720);
  loadSetting();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::on_pushButton_clicked() {
  QString str = QFileDialog::getOpenFileName(
      this, tr("Open OBJ File"), QString(), tr("OBJ Files (*.obj)"));

  if (!str.isEmpty()) {
    qDebug() << "Selected file:" << str;
    resetScrolls();
    FileProcessing(str);
  }
}

void MainWindow::FileProcessing(QString file_path) {
  openGLWidget->parseFile(&file_path);
  QString fileName = QFileInfo(file_path).fileName();
  ui->label->setText(fileName);
}

void MainWindow::on_scrollMoveX_valueChanged(int value) {
  double res = (double)value / 100;
  openGLWidget->setMovingX(res);
}

void MainWindow::on_buttonColorDots_clicked() {
  QColor col = QColorDialog::getColor();
  if (col.isValid()) {
    openGLWidget->setColorDots(col);
    openGLWidget->update();
  }
}

void MainWindow::on_scrollBarThicknessDots_valueChanged(int value) {
  openGLWidget->setThicknessOfDots(value);
  openGLWidget->update();
}

void MainWindow::on_buttonColorLine_clicked() {
  QColor col = QColorDialog::getColor();
  if (col.isValid()) {
    openGLWidget->setColorLine(col);
    openGLWidget->update();
  }
}

void MainWindow::on_scrollBarThicknessLine_valueChanged(int value) {
  openGLWidget->setLineThickness(value);
  openGLWidget->update();
}

void MainWindow::on_boxTypeLine_activated(int index) {
  if (index == 0) {
    openGLWidget->setMLineType(index);
  } else {
    openGLWidget->setMLineType(index);
  }
  openGLWidget->update();
}

void MainWindow::on_boxTypeDots_activated(int index) {
  if (index >= 0 && index < 3) {
    openGLWidget->setMDotsType(index);
  }
  openGLWidget->update();
}

void MainWindow::on_buttonColorBack_clicked() {
  QColor col = QColorDialog::getColor();
  if (col.isValid()) {
    openGLWidget->setColorBack(col);
    openGLWidget->update();
  }
}

void MainWindow::on_boxTypeProjection_activated(int index) {
  if (index == 0) {
    static_cast<MyOpenGLWidget *>(openGLWidget)->setOrthoProjection(true);
  } else if (index == 1) {
    static_cast<MyOpenGLWidget *>(openGLWidget)->setOrthoProjection(false);
  }
  openGLWidget->update();
}

void MainWindow::on_scrollMoveY_valueChanged(int value) {
  double res = (double)value / 100;
  openGLWidget->setMovingY(res);
}

void MainWindow::on_scrollMoveZ_valueChanged(int value) {
  double res = (double)value / 100;
  openGLWidget->setMovingZ(res);
}

void MainWindow::on_scrollRotationX_valueChanged(int value) {
  double res = (double)value;
  openGLWidget->setRotationX(res);
}

void MainWindow::on_scrollRotationY_valueChanged(int value) {
  double res = (double)value;
  openGLWidget->setRotationY(res);
}

void MainWindow::on_scrollRotationZ_valueChanged(int value) {
  double res = (double)value;
  openGLWidget->setRotationZ(res);
}


void MainWindow::resetScrolls() {
  openGLWidget->resetSliders();
  ui->scrollMoveX->setValue(0);
  ui->scrollMoveY->setValue(0);
  ui->scrollMoveZ->setValue(0);
  ui->scrollRotationX->setValue(0);
  ui->scrollRotationY->setValue(0);
  ui->scrollRotationZ->setValue(0);
}

void MainWindow::on_buttonScreen_clicked() {
  QPixmap screenshot = openGLWidget->grab();
  QString file_path;
  if (ui->radioButtonBMP->isChecked()) {
    file_path = QFileDialog::getSaveFileName(this, "Save Screenshot", "",
                                             "Images (*.bmp)");
    qDebug() << "screen image .bmp";
  } else if (ui->radioButtonJPEG->isChecked()) {
    file_path = QFileDialog::getSaveFileName(this, "Save Screenshot", "",
                                             "Images (*.jpeg)");
    qDebug() << "screen image .jpeg";
  }
  if (!file_path.isEmpty()) {
    screenshot.save(file_path);
  }
}

void MainWindow::on_buttonGif_clicked() {
  QString file_path =
      QFileDialog::getSaveFileName(this, "Save gif", "", "GIF (*.gif)");
  if (!file_path.isEmpty()) {
    GifMove gif_creator;
    gif_creator.createGif(file_path, openGLWidget, ui->buttonGif);
    qDebug() << "gif";
  }
}

void MainWindow::saveSettings() {
  Caretaker save;
  save.settingsOpenGLWidget(openGLWidget);
  save.mainWindowScrollMove(ui->scrollMoveX->value(), ui->scrollMoveY->value(),
                            ui->scrollMoveZ->value());
  save.mainWindowScrollRotate(ui->scrollRotationX->value(),
                              ui->scrollRotationY->value(),
                              ui->scrollRotationZ->value());
  save.mainWindowScrollScale(ui->scrollBarThicknessDots->value(),
                             ui->scrollBarThicknessLine->value());
  save.mainWindowRadioButton(ui->radioButtonBMP->isChecked(),
                             ui->radioButtonJPEG->isChecked());
  save.saveSettings();
}

void MainWindow::loadSetting() {
  SettingsMemenro settingsWindow;
  settingsWindow.settingViewer(openGLWidget);
  ui->scrollMoveX->setValue(settingsWindow.moveX);
  ui->scrollMoveY->setValue(settingsWindow.moveY);
  ui->scrollMoveZ->setValue(settingsWindow.moveZ);
  ui->scrollRotationX->setValue(settingsWindow.rotateX);
  ui->scrollRotationY->setValue(settingsWindow.rotateY);
  ui->scrollRotationZ->setValue(settingsWindow.rotateZ);
  ui->boxTypeLine->setCurrentIndex(settingsWindow.typeLine);
  ui->boxTypeDots->setCurrentIndex(settingsWindow.typeDots);
  ui->boxTypeProjection->setCurrentIndex(!settingsWindow.typePjoction);
  ui->scrollBarThicknessLine->setValue(settingsWindow.lineThickness);
  ui->scrollBarThicknessDots->setValue(settingsWindow.dotsThickness);
  ui->radioButtonJPEG->setChecked(settingsWindow.jpeg);
  ui->radioButtonBMP->setChecked(settingsWindow.bmp);
}

void MainWindow::on_pushButton_2_clicked()
{
    openGLWidget->setScale(-10.);
}


void MainWindow::on_pushButton_3_clicked()
{
    openGLWidget->setScale(10.);
}

