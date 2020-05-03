#include "gphotocontroller.h"
#include "gphoto.h"

#include "camerahandler.h"
#include <QDebug>
#include <gphoto2/gphoto2-port-info-list.h>

#include <bits/stdc++.h>
#include <fcntl.h>
#include <unistd.h>

GPhotoController::GPhotoController() {
  // TODO: handle return values
  context = gp_context_new();

  // loading abilities from libGPhoto2 camera drivers
  gp_abilities_list_new(&abilities);
  gp_abilities_list_load(abilities, context);

  gp_port_info_list_new(&portinfolist);
  gp_port_info_list_load(portinfolist);
  gp_port_info_list_count(portinfolist);
}

GPhotoController::~GPhotoController() {
  gp_port_info_list_free(portinfolist);
  gp_abilities_list_free(abilities);
  gp_context_unref(context);
}

QList<QPair<QString, QString>> GPhotoController::getCameraList() {
  return GPhoto::getCameraList(context);
}

void GPhotoController::selectCamera(QString model, QString port) {
  handler = new CameraHandler(model, port, abilities);

  const char *portData = port.toLocal8Bit().constData();
  int path = gp_port_info_list_lookup_path(portinfolist, portData);

  GPPortInfo portInfo;
  gp_port_info_list_get_info(portinfolist, path, &portInfo);
  handler->setPortInfo(portInfo);

  return;
  qDebug() << "check 001" << endl;

  CameraFile *file;
  int r;
  int fd;

  //  FILE *pipeout = popen("ffmpeg -i - -vcodec rawvideo -pix_fmt yuv420p "
  //                        "-threads 0 -f v4l2 /dev/video2",
  //                        "w");

  FILE *pipeout = popen("gst-launch-1.0 fdsrc ! decodebin3 name=dec ! queue "
                        "! videoconvert ! v4l2sink device=/dev/video2",
                        "w");

  qDebug() << pipeout << endl;
  fd = dup(fileno(pipeout));
  qDebug() << fd << endl;
  gp_file_new_from_fd(&file, fd);

  int frames = 30;
  while (frames--) {
    qDebug() << "frames: " << frames << endl;

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

  delete handler;
}
