#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

#include <QPainter>
#include <QTimer>
#include <QWidget>
#include <QApplication>

#include "../../../brick_game/brickgame.h"

class GameDisplay : public QWidget {
  Q_OBJECT
 public:
  explicit GameDisplay(QWidget* parent = nullptr);
  ~GameDisplay();
  void MakeFrame();
  void ChangeGame(s21::Model*&& Game);

  s21::UserAction_t keySignal;
  bool keyHold;

 protected:
  void paintEvent(QPaintEvent* event) override;

  void userInput(s21::UserAction_t action, bool hold);

 private:
  s21::GameInfo_t gameData;
  QTimer* timer;
  s21::Controller* contrl;
  void PaintPlayMode(QPainter& painter);
  void PaintDataInfo(QPainter& painter);
 signals:
};

#endif  // GAMEDISPLAY_H
