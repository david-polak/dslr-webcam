#ifndef ISTREAMER_H
#define ISTREAMER_H

#include <QDebug>
#include <QThread>
#include <stdio.h>

class IStreamer : public QThread {
public:
  virtual ~IStreamer() { qDebug() << "~IStreamer()"; };
  virtual void run() = 0;
  virtual void setFd(int fd) = 0;
};

#endif
