#include "brickgame.h"

#include "./ui_brickgame.h"

BrickGame::BrickGame(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::BrickGame) {
  ui->setupUi(this);
}

BrickGame::~BrickGame() { delete ui; }

void BrickGame::keyPressEvent(QKeyEvent *event) {
  bool myKey = true;
  switch (event->key()) {
    case Qt::Key_Left:
      ui->widget->keySignal = s21::Left;
      break;
    case Qt::Key_Right:
      ui->widget->keySignal = s21::Right;
      break;
    case Qt::Key_Up:
      ui->widget->keySignal = s21::Up;
      break;
    case Qt::Key_Down:
      ui->widget->keySignal = s21::Down;
      break;
    case Qt::Key_Space:
      ui->widget->keySignal = s21::Action;
      break;
    case Qt::Key_Escape:
      ui->widget->keySignal = s21::Pause;
      break;
    case Qt::Key_Q:
      ui->widget->keySignal = s21::Terminate;
      break;
    default:
      myKey = false;
  }
  ui->widget->keyHold = myKey && true;
}

void BrickGame::on_pushButton_clicked() {
  ui->widget->ChangeGame(new s21::SnakeModel(
      (QApplication::applicationDirPath() + "/Snake.txt").toLatin1().data()));
}

void BrickGame::on_pushButton_2_clicked() {
  ui->widget->ChangeGame(new s21::TetrisModel(
      (QApplication::applicationDirPath() + "/Tetris.txt").toLatin1().data()));
}
