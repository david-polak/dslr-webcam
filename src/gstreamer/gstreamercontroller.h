#ifndef GSTREAMERCONTROLLER_H
#define GSTREAMERCONTROLLER_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

class GStreamerController {
public:
  GStreamerController();
  ~GStreamerController();

  void stop();
  void start();
  int getFd();

protected:
  FILE *output;
  int fd;
};

#endif // GSTREAMERCONTROLLER_H
