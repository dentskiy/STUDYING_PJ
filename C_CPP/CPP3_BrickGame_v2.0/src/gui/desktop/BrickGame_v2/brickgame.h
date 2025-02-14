#ifndef BRICKGAME_H
#define BRICKGAME_H

#include <QKeyEvent>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class BrickGame;
}
QT_END_NAMESPACE

class BrickGame : public QMainWindow {
  Q_OBJECT

 public:
  BrickGame(QWidget *parent = nullptr);
  ~BrickGame();

  void keyPressEvent(QKeyEvent *event) override;

 private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

 private:
  Ui::BrickGame *ui;
};
#endif  // BRICKGAME_H
