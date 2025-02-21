#include "gifmove.h"

#include "../../../libs/gif.h"

void GifMove::createGif(const QString &file_path, QWidget *widget,
                        QPushButton *button) {
  QImage img(widget->size(), QImage::Format_RGB32);
  QPainter painter(&img);
  QTime die_time;
  GifWriter gif;
  GifBegin(&gif, file_path.toLocal8Bit().data(), 640, 480, 20);
  for (int i = 0; i < 50; ++i) {
    button->setText(QString::number(i / 10.0, 'f', 1) + "s");
    widget->render(&painter);
    QImage img950_480 = img.scaled(QSize(640, 480));
    GifWriteFrame(&gif, img950_480.bits(), 640, 480, 10);
    die_time = QTime::currentTime().addMSecs(100);
    while (QTime::currentTime() <= die_time)
      QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
  }
  button->setText("SAVE GIF");
  GifEnd(&gif);
}
