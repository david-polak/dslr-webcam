#ifndef GSTREAMERCONTROLLER_H
#define GSTREAMERCONTROLLER_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <QStringList>

class GStreamerController {
public:
  GStreamerController();
  ~GStreamerController();

  void stop();
  void start();
  int getFd();

  void setV4L2Device(QString device);
  QStringList listV4L2Devices();

protected:
  QString device;
  FILE *output = NULL;
  int fd;
  bool running = false;
};

#endif // GSTREAMERCONTROLLER_H
