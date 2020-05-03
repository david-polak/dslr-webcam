#include "camerastreamer.h"

#include <QDebug>
#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-file.h>

void CameraStreamer::setCameraHandler(CameraHandler *handler) {
  this->handler = handler;
}
void CameraStreamer::setContext(GPContext *context) { this->context = context; }

CameraStreamer::~CameraStreamer() {
  qDebug() << "~CameraStreamer()" << endl;
  gp_file_unref(this->file);
}

void CameraStreamer::setFd(int fd) {
  qDebug() << "CameraStreamer::setFd(" << fd << ")" << endl;
  gp_file_new_from_fd(&this->file, fd);
}

void CameraStreamer::run() {
  int r;

  forever {
    if (this->isInterruptionRequested()) {
      qDebug() << "Interruption requested";
      return;
    }

    r = gp_camera_capture_preview(handler->camera, this->file, context);
    if (r < 0) {
      qDebug() << "Movie capture error... Exiting.";
      break;
    }
  }
}
