#include "gamedisplay.h"

GameDisplay::GameDisplay(QWidget* parent) : QWidget{parent} {
  keySignal = s21::Action;
  keyHold = false;
  timer = new QTimer();
  connect(timer, &QTimer::timeout, this, &GameDisplay::MakeFrame);
  contrl = new s21::Controller(new s21::TetrisModel(
      (QApplication::applicationDirPath() + "/Tetris.txt").toLatin1().data()));
  gameData = contrl->updateCurrentState();
  timer->start(1000 / 50);
}

GameDisplay::~GameDisplay() {
  delete timer;
  delete contrl;
}

void GameDisplay::MakeFrame() {
  contrl->userInput(keySignal, keyHold);
  keyHold = false;
  gameData = contrl->updateCurrentState();
  update();
}

void GameDisplay::ChangeGame(s21::Model*&& Game) {
  contrl->ChangeModel(std::move(Game));
}

void GameDisplay::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);

  static const int& width(this->width());
  static const int& heigth(this->height());

  QPainter painter(this);
  QFont NPlayFont("Times", 35, -1, false);
  QFont PlayFont("Times", 18, -1, false);

  painter.fillRect(0, 0, this->width(), this->height(), QColor(0, 0, 0));

  switch (gameData.pause) {
    case s21::ModelPlay:
      painter.setFont(PlayFont);
      PaintPlayMode(painter);
      break;
    case s21::ModelPause:
      painter.setFont(NPlayFont);
      painter.drawText(width / 2 - 55, heigth / 2, "PAUSE");
      break;
    case s21::GameOver:
      painter.setFont(NPlayFont);
      painter.drawText(width / 2 - 110, heigth / 2, "GAME OVER");
      break;
  }
}

void GameDisplay::PaintPlayMode(QPainter& painter) {
  for (int i{}; i < s21::kHeight; i++) {
    for (int j{}; j < s21::kWidth; j++) {
      if (gameData.field[i][j] == s21::kMoveCell) {
        painter.setBrush(QBrush(QColor(0, 255, 0)));
      } else if (gameData.field[i][j] == s21::kStaticCell) {
        painter.setBrush(QBrush(QColor(255, 0, 0)));
      } else {
        painter.setBrush(QBrush(QColor(255, 255, 255, 50)));
      }
      painter.drawRect(j * 20 + 30, i * 20 + 20, 20, 20);
    }
  }
  PaintDataInfo(painter);
}

void GameDisplay::PaintDataInfo(QPainter& painter) {
  static const int leftLVL = 60 + 20 * 10;
  int topLVL = 50;

  if (gameData.high_score >= 0) {
    painter.drawText(leftLVL, topLVL, "High score: ");
    topLVL += 20;
    painter.drawText(leftLVL, topLVL,
                     QString(QString::number(gameData.high_score)));
    topLVL += 40;
  }
  if (gameData.score >= 0) {
    painter.drawText(leftLVL, topLVL, "score: ");
    topLVL += 20;
    painter.drawText(leftLVL, topLVL, QString(QString::number(gameData.score)));
    topLVL += 40;
  }
  painter.drawText(leftLVL, topLVL,
                   "level: " + QString(QString::number(gameData.level)));
  topLVL += 40;

  if (gameData.next) {
    painter.drawText(leftLVL, topLVL, "next:");
    topLVL += 20;
    for (int i{}; i < 4; i++) {
      for (int j{}; j < 4; j++) {
        if (gameData.next[i][j])
          painter.setBrush(QBrush(QColor(0, 255, 0)));
        else
          painter.setBrush(QBrush(QColor(255, 255, 255, 50)));
        painter.drawRect(j * 20 + leftLVL, i * 20 + topLVL, 20, 20);
      }
    }
  }
}
