#include "camerastreamer.h"

#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-file.h>

#include <QDebug>

void CameraStreamer::setCamera(Camera *camera) {
  this->camera = camera;
}
void CameraStreamer::setContext(GPContext *context) {
  this->context = context;
}

CameraStreamer::~CameraStreamer() {
  qDebug() << "~CameraStreamer()";
}

void CameraStreamer::setFd(int fd) {
  qDebug() << "CameraStreamer::setFd(" << fd << ")";
  gp_file_new_from_fd(&this->file, fd);
}

void CameraStreamer::run() {
  int r;

  forever {
    if (this->isInterruptionRequested()) {
      //      qDebug() << "Interruption requested";
      return;
    }

    r = gp_camera_capture_preview(camera, this->file, context);
    if (r < 0) {
      qDebug() << "Movie capture error... Exiting.";
      break;
    }
  }
}
