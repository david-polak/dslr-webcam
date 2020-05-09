#include "dslrwebcam.h"
#include "gphoto/camerahandler.h"
#include "gphoto/gphoto.h"

#include "src/gstreamer/gstreamercontroller.h"
#include <QDebug>
#include <QTimer>
#include <gphoto2/gphoto2-port-info-list.h>

DSLRWebcam::DSLRWebcam() {
  // TODO: handle return values
  context = gp_context_new();
  gstreamer = new GStreamerController();
}

DSLRWebcam::~DSLRWebcam() {
  qDebug() << "~dslrWebcam()";

  if (cameraStreamer != NULL) {
    qDebug() << "delete cameraStreamer";
    cameraStreamer->requestInterruption();
    cameraStreamer->wait();
    delete cameraStreamer;
  }
  // TODO: cleanup streamers

  if (gstreamer != NULL) {
    qDebug() << "delete gstreamer";
    delete gstreamer;
  }

  if (handler != NULL) {
    qDebug() << "delete handler";
    delete handler;
  }

  qDebug() << "delete context";
  gp_context_unref(context);
}

QList<QPair<QString, QString>> DSLRWebcam::getCameraList() {
  return GPhoto::getCameraList(context);
}

void DSLRWebcam::setV4L2Device(QString device) {
  gstreamer->setV4L2Device(device);
}

void DSLRWebcam::selectCamera(QString model, QString port) {
  handler = new CameraHandler(model, port, context);
}

QStringList DSLRWebcam::getCameraWidgets() {
  return handler->getWidgets(GP_WIDGET_RADIO, 0);
}

void DSLRWebcam::killCurrentStreamer() {
  if (currentStreamer) {
    if (typeid(currentStreamer) == typeid(CameraStreamer)) {
      handler->setCameraStreamer(NULL);
    }
    currentStreamer->requestInterruption();
    currentStreamer->wait();
    delete currentStreamer;
    currentStreamer = NULL;
  }
}

WidgetRadioControl *DSLRWebcam::createWidgetRadioControl(QWidget *parent,
                                                         QString moniker) {
  CameraWidget *widget = handler->getWidget(moniker);

  WidgetRadioControl *control =
      new WidgetRadioControl(parent, moniker, handler, context, widget);

  return control;
}

void DSLRWebcam::interruptCamera() {
  if (typeid(currentStreamer) == typeid(CameraStreamer)) {
    killCurrentStreamer();
  }
}

void DSLRWebcam::resumeCamera() {
  if (currentStreamer == NULL) {
    useCameraStreamer();
  }
}

void DSLRWebcam::useCameraStreamer() {
  killCurrentStreamer();
  cameraStreamer = new CameraStreamer();
  cameraStreamer->setCamera(handler->camera);
  cameraStreamer->setContext(context);
  currentStreamer = cameraStreamer;
  handler->setCameraStreamer(cameraStreamer);

  int fd = gstreamer->getFd();
  currentStreamer->setFd(fd);
  currentStreamer->start();
}

void DSLRWebcam::usePictureStreamer() {
  killCurrentStreamer();
  pictureStreamer = new PictureStreamer();
  pictureStreamer->setImagePath(
      "/home/david/Data/Code/dslr-webcam/images/blank.jpg");
  currentStreamer = pictureStreamer;

  int fd = gstreamer->getFd();
  currentStreamer->setFd(fd);
  currentStreamer->start();
}

void DSLRWebcam::toggleDOF(bool enable) {
  qDebug() << "DSLRWebcam::toggleDOF(" << enable << ")";
  handler->toggleDOF(enable);
}

void DSLRWebcam::startStream() { gstreamer->start(); }
bool DSLRWebcam::isStreamRunning() { return true; }
void DSLRWebcam::pauseStream() {
  qDebug() << "pause stream";
  cameraStreamer->requestInterruption();
}

void DSLRWebcam::resumeStream() {
  qDebug() << "resume stream";
  cameraStreamer->start();
}

QStringList DSLRWebcam::getV4L2Devices() {
  return gstreamer->listV4L2Devices();
}
