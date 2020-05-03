#include "gphotocontroller.h"
#include "gphoto.h"

#include "camerahandler.h"
#include "src/gstreamer/gstreamercontroller.h"
#include <QDebug>
#include <gphoto2/gphoto2-port-info-list.h>

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
  qDebug() << "~GPhotoController()" << endl;

  if (cameraStreamer) {
    cameraStreamer->requestInterruption();
    cameraStreamer->wait();
    delete cameraStreamer;
    qDebug() << "delete cameraStreamer;" << endl;
  }
  // TODO: cleanup streamers

  if (gstreamer) {
    delete gstreamer;
  }

  if (handler) {
    delete handler;
  }

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
}

void GPhotoController::useCameraStreamer() {
  cameraStreamer = new CameraStreamer();
  cameraStreamer->setCameraHandler(handler);
  cameraStreamer->setContext(context);
  currentStreamer = cameraStreamer;
}

void GPhotoController::startStream() {
  gstreamer = new GStreamerController();
  gstreamer->start();
  int fd = gstreamer->getFd();

  currentStreamer->setFd(fd);
  currentStreamer->start();
}
bool GPhotoController::isStreamRunning() { return true; }
void GPhotoController::pauseStream() {}
