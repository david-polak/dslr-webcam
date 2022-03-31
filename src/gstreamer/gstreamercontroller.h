#ifndef GSTREAMERCONTROLLER_H
#define GSTREAMERCONTROLLER_H

#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

#include <QStringList>

class GStreamerController {
public:
  GStreamerController();
  ~GStreamerController();

  int getFd() const;

  static QStringList getV4l2Devices();
  void setV4L2Device(QString v4l2Device);

  void stop();
  void start();

protected:
  int fd;
  QString device;
  FILE *outpipe = nullptr;
};

#endif // GSTREAMERCONTROLLER_H
