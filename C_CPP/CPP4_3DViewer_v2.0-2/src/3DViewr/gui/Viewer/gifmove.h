#ifndef GIFMOVE_H
#define GIFMOVE_H

#include <QCoreApplication>
#include <QPainter>
#include <QPushButton>
#include <QString>
#include <QTime>

class GifMove {
 public:
  GifMove() = default;
  void createGif(const QString &file_path, QWidget *widget,
                 QPushButton *button);
};

#endif  // GIFMOVE_H
