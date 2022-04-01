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
}

DSLRWebcam::~DSLRWebcam() {
  qDebug() << "~dslrWebcam()";
  this->deleteCameraStreamer();
  this->deleteCameraHandler();
  this->deleteGstreamer();
  GPhoto::deleteContext(this->gphotoContext);
}

QList<QPair<QString, QString>> DSLRWebcam::getCameraList() {
  return GPhoto::getCameraList(this->gphotoContext);
}

QStringList DSLRWebcam::getV4L2Devices() {
  return GStreamerController::getV4l2Devices();
}

bool DSLRWebcam::isRunning() const {
  return this->running;
}

void DSLRWebcam::setCamera(QPair<QString, QString> camera) {
  this->camera = camera;
}

void DSLRWebcam::setV4l2Device(QString v4l2Device) {
  this->v4l2Device = v4l2Device;
}

void DSLRWebcam::createCameraHandler() {
  if (this->cameraHandler == nullptr) {
    this->cameraHandler = new CameraHandler(
        this->camera.first, this->camera.second, this->gphotoContext);
  }
}

void DSLRWebcam::start() {
  this->createCameraHandler();

  this->cameraStreamer = new CameraStreamer();
  this->cameraStreamer->setContext(this->gphotoContext);
  this->cameraStreamer->setCamera(this->cameraHandler->camera);

  if (this->gstreamer == nullptr) {
    this->gstreamer = new GStreamerController();
    this->gstreamer->setV4L2Device(v4l2Device);
    this->gstreamer->start();
  }

  this->cameraStreamer->setFd(this->gstreamer->getFd());
  this->cameraStreamer->start();

  this->running = true;
}

void DSLRWebcam::stop() {
  this->deleteCameraStreamer();
  this->deleteCameraHandler();

  this->running = false;
}

void DSLRWebcam::deleteGstreamer() {
  if (this->gstreamer == nullptr) {
    return;
  }
  this->gstreamer->stop();
  delete this->gstreamer;
  this->gstreamer = nullptr;
}

void DSLRWebcam::deleteCameraStreamer() {
  if (this->cameraStreamer == nullptr) {
    return;
  }
  this->cameraStreamer->requestInterruption();
  this->cameraStreamer->wait();
  delete this->cameraStreamer;
  this->cameraStreamer = nullptr;
}

void DSLRWebcam::deleteCameraHandler() {
  if (this->cameraHandler == nullptr) {
    return;
  }
  delete this->cameraHandler;
  this->cameraHandler = nullptr;
}

QStringList DSLRWebcam::getCameraWidgets() {
  this->createCameraHandler();
  return cameraHandler->getWidgets(GP_WIDGET_RADIO, 0);
}

QString DSLRWebcam::getWidgetValue(const QString &moniker) {
  this->createCameraHandler();
  return this->cameraHandler->getWidgetValue(moniker);
}

QStringList DSLRWebcam::getWidgetValues(const QString &moniker) {
  this->createCameraHandler();
  return this->cameraHandler->getWidgetValues(moniker);
}

void DSLRWebcam::setWidgetValue(const QString &moniker, const QString &value) {
  this->createCameraHandler();
  this->interruptCamera();
  this->cameraHandler->setWidgetValue(moniker, value);
  this->resumeCamera();
}

void DSLRWebcam::interruptCamera() {
  if (this->cameraStreamer != nullptr) {
    this->cameraStreamer->requestInterruption();
    this->cameraStreamer->wait();
  }
}

void DSLRWebcam::resumeCamera() {
  if (this->cameraStreamer != nullptr) {
    this->cameraStreamer->start();
  }
}

void DSLRWebcam::setTrueDepthOfField(bool value) {
  this->createCameraHandler();
  this->cameraHandler->setTrueDepthOfField(value);
}
