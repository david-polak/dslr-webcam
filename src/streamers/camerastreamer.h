#ifndef CAMERASTREAMER_H
#define CAMERASTREAMER_H

#include <QThread>

#include "istreamer.h"
#include <gphoto2/gphoto2-camera.h>

class CameraStreamer : public IStreamer {
public:
  ~CameraStreamer();
  void run() override;
  void setFd(int fd) override;

  void setCamera(Camera *camera);
  void setContext(GPContext *context);

private:
  GPContext *context;
  CameraFile *file;
  Camera *camera;
};

#endif
