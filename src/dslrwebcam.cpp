#include "dslrwebcam.h"

#include <gphoto2/gphoto2-port-info-list.h>

#include <QDebug>
#include <QSettings>
#include <QTimer>

#include "gphoto/camerahandler.h"
#include "gphoto/gphoto.h"
#include "src/gstreamer/gstreamercontroller.h"

DSLRWebcam::DSLRWebcam() {
  this->gphotoContext = GPhoto::createContext();

  //  //  gstreamer = new GStreamerController();
  //
  //  QSettings settings;
}
DSLRWebcam::~DSLRWebcam() {
  GPhoto::deleteContext(this->gphotoContext);
  //  qDebug() << "~dslrWebcam()";
  //
  //  if (cameraStreamer != NULL) {
  //    qDebug() << "delete cameraStreamer";
  //    cameraStreamer->requestInterruption();
  //    cameraStreamer->wait();
  //    delete cameraStreamer;
  //  }
  //  // TODO: cleanup streamers
  //
  //  if (gstreamer != NULL) {
  //    qDebug() << "delete gstreamer";
  //    delete gstreamer;
  //  }
  //
  //  if (cameraHandler != NULL) {
  //    qDebug() << "delete handler";
  //    delete cameraHandler;
  //  }
  //
  //  qDebug() << "delete context";
  //  gp_context_unref(gphotoContext);
}

QList<QPair<QString, QString>> DSLRWebcam::getCameraList() {
  return GPhoto::getCameraList(this->gphotoContext);
}

// ######### OLD ############################################################

void DSLRWebcam::startStream() {
  qDebug() << "Start stream";
  gstreamer = new GStreamerController();
  gstreamer->setV4L2Device(v4l2Device);
  gstreamer->start();
}

void DSLRWebcam::stopStream() {
  qDebug() << "Stop stream";
  gstreamer->stop();
  delete gstreamer;
  gstreamer = NULL;
}

void DSLRWebcam::startCameraStreamer() {
  qDebug() << "Start camera streamer";
  killCurrentStreamer();
  selectCamera(cameraModel, cameraPort);

  cameraStreamer = new CameraStreamer();
  cameraStreamer->setCamera(cameraHandler->camera);
  cameraStreamer->setContext(gphotoContext);
  currentStreamer = cameraStreamer;
  cameraHandler->setCameraStreamer(cameraStreamer);

  int fd = gstreamer->getFd();
  currentStreamer->setFd(fd);
  currentStreamer->start();
}

void DSLRWebcam::stopCameraStreamer() {
  killCurrentStreamer();
  deleteCameraHandler();
}

void DSLRWebcam::deleteCameraHandler() {
  if (cameraHandler != NULL) {
    delete cameraHandler;
    cameraHandler = NULL;
  }
}

bool DSLRWebcam::isStreamRunning() {
  return gstreamer != NULL;
}
bool DSLRWebcam::isStreamerRunning() {
  return currentStreamer != NULL;
}

void DSLRWebcam::setV4L2Device(QString v4l2Device) {
  this->v4l2Device = v4l2Device;
}

void DSLRWebcam::selectCamera(QString model, QString port) {
  cameraModel = model;
  cameraPort = port;
  deleteCameraHandler();
  cameraHandler = new CameraHandler(cameraModel, cameraPort, gphotoContext);
}

QStringList DSLRWebcam::getCameraWidgets() {
  return cameraHandler->getWidgets(GP_WIDGET_RADIO, 0);
}

void DSLRWebcam::killCurrentStreamer() {
  qDebug() << "Stopping streamer";
  if (!currentStreamer) {
    return;
  }
  if (typeid(currentStreamer) == typeid(CameraStreamer)) {
    cameraHandler->setCameraStreamer(NULL);
  }
  currentStreamer->requestInterruption();
  currentStreamer->wait();
  delete currentStreamer;
  currentStreamer = NULL;
}

WidgetRadioControl *
DSLRWebcam::createWidgetRadioControl(QWidget *parent, QString moniker) {
  CameraWidget *widget = cameraHandler->getWidget(moniker);

  WidgetRadioControl *control = new WidgetRadioControl(
      parent, moniker, cameraHandler, gphotoContext, widget);

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
  cameraStreamer->setCamera(cameraHandler->camera);
  cameraStreamer->setContext(gphotoContext);
  currentStreamer = cameraStreamer;
  cameraHandler->setCameraStreamer(cameraStreamer);

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
  cameraHandler->toggleDOF(enable);
}

void DSLRWebcam::startStreamOld() {
  gstreamer->start();
}

void DSLRWebcam::pauseStreamOld() {
  qDebug() << "pause stream";
  cameraStreamer->requestInterruption();
}

void DSLRWebcam::resumeStreamOld() {
  qDebug() << "resume stream";
  cameraStreamer->start();
}

QStringList DSLRWebcam::getV4L2Devices() {
  return gstreamer->listV4L2Devices();
}
