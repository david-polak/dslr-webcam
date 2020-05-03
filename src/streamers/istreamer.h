#ifndef ISTREAMER_H
#define ISTREAMER_H

#include <QThread>
#include <stdio.h>

class IStreamer : public QThread {
public:
  virtual ~IStreamer(){};
  virtual void run() = 0;
  virtual void setFile(FILE *fd) = 0;
};

#endif
