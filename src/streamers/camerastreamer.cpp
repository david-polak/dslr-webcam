#include "camerastreamer.h"

#include <QDebug>
#include <gphoto2/gphoto2-camera.h>

#include <bits/stdc++.h>
#include <fcntl.h>
#include <unistd.h>

void CameraStreamer::setCameraHandler(CameraHandler *handler) {
  this->handler = handler;
}

void CameraStreamer::setContext(GPContext *context) { this->context = context; }

void CameraStreamer::setFile(FILE *fd) { this->fd = fd; }

void CameraStreamer::run() {
  qDebug() << "check 001" << endl;

  CameraFile *file;
  int r;
  int fd;

  FILE *pipeout = popen("gst-launch-1.0 fdsrc ! decodebin3 name=dec ! queue "
                        "! videoconvert ! v4l2sink device=/dev/video2",
                        "w");

  qDebug() << pipeout << endl;
  fd = dup(fileno(pipeout));
  qDebug() << fd << endl;
  gp_file_new_from_fd(&file, fd);

  forever {
    if (this->isInterruptionRequested()) {
      return;
    }

    r = gp_camera_capture_preview(handler->camera, file, context);
    if (r < 0) {
      qDebug() << "Movie capture error... Exiting.";
      break;
    }
  }

  qDebug() << "end" << endl;
  fflush(pipeout);
  close(fd);
  gp_file_unref(file);
  qDebug() << "kill" << endl;
  system("killall gst-launch-1.0"); // :P I'll deal with it later
  pclose(pipeout);
  qDebug() << "terminated" << endl;
}
