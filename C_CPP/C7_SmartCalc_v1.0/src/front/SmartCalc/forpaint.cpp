#include "forpaint.h"

forPaint::forPaint(QWidget *parent) : QWidget{parent} {
  for (int i = 0; i < GRAPHP; i++) {
    x[i] = i;
    y[i] = -1;
  }
}

void forPaint::paintEvent(QPaintEvent *event) {
  QPainter pan;
  QRect rect = event->rect();
  double stepX = double(this->width()) / double(GRAPHP);
  double stepY = double(this->height()) / 1000.;
  pan.begin(this);
  pan.fillRect(0, 0, this->width(), this->height(), QColor(255, 255, 255));
  pan.setPen(QPen(QColor(0, 0, 0)));
  pan.drawLine(this->width() / 2, 0, this->width() / 2, this->height());
  pan.drawLine(0, this->height() / 2, this->width(), this->height() / 2);
  pan.drawText(0, this->height() / 2 + 20, "-5");
  pan.drawText(this->width() - 10, this->height() / 2 + 20, "5");
  pan.drawText(this->width() / 2 + 5, this->height() - 5, "-5");
  pan.drawText(this->width() / 2 + 5, 15, "5");
  pan.setPen(QPen(QColor(255, 0, 0)));
  for (int i = 0; i < GRAPHP - 1; i++) {
    if (rect.contains(x[i] * stepX, y[i] * stepY) &&
        rect.contains(x[i + 1] * stepX, y[i + 1] * stepY))
      pan.drawLine(x[i] * stepX, y[i] * stepY, x[i + 1] * stepX,
                   y[i + 1] * stepY);
  }
  pan.end();
}

void forPaint::setFunc(double *func) {
  for (int i = 0; i < GRAPHP; i++) {
    y[i] = 1000 / 2 - func[i] * 100.;
  }
  this->update();
}
