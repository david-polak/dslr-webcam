#ifndef STREAM_H
#define STREAM_H

#include <QThread>

#include "istreamer.h"
#include "src/gphoto/camerahandler.h"

class CameraStreamer : public IStreamer {
public:
  ~CameraStreamer();
  void run() override;
  void setFd(int fd) override;

  void setCameraHandler(CameraHandler *handler);
  void setContext(GPContext *context);

private:
  CameraHandler *handler;
  GPContext *context;
  CameraFile *file;
};

#endif // STREAM_H
