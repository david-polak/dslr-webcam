#ifndef GPHOTOCONTROLLER_H
#define GPHOTOCONTROLLER_H

#include <gphoto2/gphoto2-abilities-list.h>
#include <gphoto2/gphoto2-context.h>

#include <QList>
#include <QObject>
#include <QString>

#include "src/gphoto/camerahandler.h"
#include "src/gstreamer/gstreamercontroller.h"
#include "src/streamers/camerastreamer.h"
#include "src/streamers/istreamer.h"
#include "src/streamers/picturestreamer.h"

class DSLRWebcam : public QObject {
  Q_OBJECT
public:
  DSLRWebcam();
  ~DSLRWebcam();

  static QStringList getV4L2Devices();
  bool isRunning() const;

  void setCamera(QPair<QString, QString> camera);
  void setV4l2Device(QString v4l2Device);

  void start();
  void stop();

  void interruptCamera();
  void resumeCamera();

  // CameraHandler proxies
  QList<QPair<QString, QString>> getCameraList();
  QStringList getCameraWidgets();
  QString getWidgetValue(const QString &moniker);
  QStringList getWidgetValues(const QString &moniker);
  void setWidgetValue(const QString &moniker, const QString &value);
  void setTrueDepthOfField(bool value);

protected:
  bool running = false;
  GPContext *gphotoContext = nullptr;
  GStreamerController *gstreamer = nullptr;
  CameraStreamer *cameraStreamer = nullptr;
  CameraHandler *cameraHandler = nullptr;

  QPair<QString, QString> camera;
  QString v4l2Device;

  void createCameraHandler();

  void deleteGstreamer();
  void deleteCameraStreamer();
  void deleteCameraHandler();
};

#endif
