#include "dslrwebcam.h"
#include "gphoto/camerahandler.h"
#include "gphoto/gphoto.h"

#include "src/gstreamer/gstreamercontroller.h"
#include <QDebug>
#include <gphoto2/gphoto2-port-info-list.h>

DSLRWebcam::DSLRWebcam() {
  // TODO: handle return values
  context = gp_context_new();

  // loading abilities from libGPhoto2 camera drivers
  gp_abilities_list_new(&abilities);
  gp_abilities_list_load(abilities, context);

  gp_port_info_list_new(&portinfolist);
  gp_port_info_list_load(portinfolist);
  gp_port_info_list_count(portinfolist);
}

DSLRWebcam::~DSLRWebcam() {
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

QList<QPair<QString, QString>> DSLRWebcam::getCameraList() {
  return GPhoto::getCameraList(context);
}

void DSLRWebcam::selectCamera(QString model, QString port) {
  handler = new CameraHandler(model, port, abilities);

  const char *portData = port.toLocal8Bit().constData();
  int path = gp_port_info_list_lookup_path(portinfolist, portData);

  GPPortInfo portInfo;
  gp_port_info_list_get_info(portinfolist, path, &portInfo);
  handler->setPortInfo(portInfo);
}

void DSLRWebcam::useCameraStreamer() {
  cameraStreamer = new CameraStreamer();
  cameraStreamer->setCameraHandler(handler);
  cameraStreamer->setContext(context);
  currentStreamer = cameraStreamer;

  int fd = gstreamer->getFd();
  currentStreamer->setFd(fd);
  currentStreamer->start();
}

void DSLRWebcam::startStream() {
  gstreamer = new GStreamerController();
  gstreamer->start();
}
bool DSLRWebcam::isStreamRunning() { return true; }
void DSLRWebcam::pauseStream() {
  qDebug() << "pause stream" << endl;
  cameraStreamer->requestInterruption();
}

void DSLRWebcam::resumeStream() {
  qDebug() << "resume stream" << endl;
  cameraStreamer->start();
}
