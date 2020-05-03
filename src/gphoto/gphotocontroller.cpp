#include "gphotocontroller.h"
#include "gphoto.h"

#include "camerahandler.h"
#include <QDebug>
#include <gphoto2/gphoto2-port-info-list.h>

#include <unistd.h>

GPhotoController::GPhotoController() {
  // TODO: handle return values
  context = gp_context_new();

  // loading abilities from libGPhoto2 camera drivers
  gp_abilities_list_new(&abilities);
  gp_abilities_list_load(abilities, context);
}

GPhotoController::~GPhotoController() {
  gp_abilities_list_free(abilities);
  gp_context_unref(context);
}

QList<QPair<QString, QString>> GPhotoController::getCameraList() {
  return GPhoto::getCameraList(context);
}

static GPPortInfoList *portinfolist = NULL;

void GPhotoController::testCamera(QString model, QString port) {
  CameraHandler *handler = new CameraHandler(model, port, abilities);

  int p;
  GPPortInfo pi;

  if (!portinfolist) {
    gp_port_info_list_new(&portinfolist);
    gp_port_info_list_load(portinfolist);
    gp_port_info_list_count(portinfolist);
  }

  const char *portData = port.toLocal8Bit().constData();

  p = gp_port_info_list_lookup_path(portinfolist, portData);

  gp_port_info_list_get_info(portinfolist, p, &pi);
  gp_camera_set_port_info(handler->camera, pi);

  qDebug() << "check 001" << endl;

  CameraFile *file;
  int r;
  int fd;

  //  FILE *pipeout = popen("ffmpeg -i - -vcodec rawvideo -pix_fmt yuv420p "
  //                        "-threads 0 -f v4l2 /dev/video2",
  //                        "w");

  FILE *pipeout = popen("gst-launch-1.0 -e fdsrc ! decodebin3 name=dec ! queue "
                        "! videoconvert ! v4l2sink device=/dev/video2",
                        "w");

  qDebug() << pipeout << endl;
  fd = dup(fileno(pipeout));
  qDebug() << fd << endl;
  gp_file_new_from_fd(&file, fd);

  int frames = 100;
  while (frames--) {
    qDebug() << "frames: " << frames << endl;

    const char *mime;
    r = gp_camera_capture_preview(handler->camera, file, context);
    if (r < 0) {
      qDebug() << "Movie capture error... Exiting.";
      break;
    }
  }

  qDebug() << "end" << endl;
  gp_file_unref(file);

  // fflush(pipeout);
  pclose(pipeout);
  delete handler;
}
