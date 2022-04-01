#ifndef GPHOTOCONTROLLER_H
#define GPHOTOCONTROLLER_H

#include <gphoto2/gphoto2-abilities-list.h>
#include <gphoto2/gphoto2-context.h>

#include <QList>
#include <QObject>
#include <QString>

#include "src/gphoto/camerahandler.h"
#include "src/gstreamer/gstreamercontroller.h"
//#include "src/gui/widgetradiocontrol.h"
#include "src/streamers/camerastreamer.h"
#include "src/streamers/istreamer.h"
#include "src/streamers/picturestreamer.h"

class DSLRWebcam : public QObject {
  Q_OBJECT
public:
  DSLRWebcam();
  ~DSLRWebcam();

  QList<QPair<QString, QString>> getCameraList();
  static QStringList getV4L2Devices();
  QStringList getCameraWidgets();
  bool isRunning() const;

  void setCamera(QPair<QString, QString> camera);
  void setV4l2Device(QString v4l2Device);

  void start();
  void stop();

  QString getWidgetValue(const QString &moniker);

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

  ///////// old

  // public:
  //
  //   WidgetRadioControl *
  //   createWidgetRadioControl(QWidget *parent, QString moniker);
  //
  //   void startStream();
  //   void stopStream();
  //
  //   void setV4L2Device(QString v4l2Device);
  //
  //   void selectCamera(QString model, QString port);
  //   void startStreamOld();
  //
  //   bool isStreamRunning();
  //   bool isStreamerRunning();
  //
  //   void pauseStreamOld();
  //   void resumeStreamOld();
  //
  //   void startCameraStreamer();
  //   void stopCameraStreamer();
  //
  //   void useCameraStreamer();
  //   void usePictureStreamer();
  //   void killCurrentStreamer();
  //
  //   void interruptCamera();
  //   void resumeCamera();

public slots:

  //  void toggleDOF(bool enable);

protected:
  //  CameraHandler *cameraHandler = NULL;

  //  IStreamer *currentStreamer = NULL;
  //  CameraStreamer *cameraStreamer = NULL;
  //  PictureStreamer *pictureStreamer = NULL;
  //
  //  QString cameraModel;
  //  QString cameraPort;
  //
  //  void deleteCameraHandler();
};

#endif
