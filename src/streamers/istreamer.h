#ifndef ISTREAMER_H
#define ISTREAMER_H

#include <stdio.h>

#include <QDebug>
#include <QThread>

class IStreamer : public QThread {
public:
  virtual ~IStreamer() {
    qDebug() << "~IStreamer()";
  };
  virtual void run() = 0;
  virtual void setFd(int fd) = 0;
};

#endif
