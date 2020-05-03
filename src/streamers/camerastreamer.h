#ifndef STREAM_H
#define STREAM_H

#include <QThread>

#include "istreamer.h"
#include "src/gphoto/camerahandler.h"

class CameraStreamer : public IStreamer {
public:
  void run() override;
  void setFile(FILE *fd) override;

  void setCameraHandler(CameraHandler *handler);
  void setContext(GPContext *context);

private:
  CameraHandler *handler;
  GPContext *context;
  FILE *fd;
};

#endif // STREAM_H
