#ifndef FORPAINT_H
#define FORPAINT_H

#include <QBrush>
#include <QColor>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QWidget>

#define GRAPHP 100

class forPaint : public QWidget {
  Q_OBJECT
 public:
  explicit forPaint(QWidget *parent = nullptr);
  void setFunc(double *func);

 protected:
  void paintEvent(QPaintEvent *event);

 private:
  int x[GRAPHP];
  int y[GRAPHP];

 signals:
};

#endif  // FORPAINT_H
