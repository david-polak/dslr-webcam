#ifndef GPHOTOCONTROLLER_H
#define GPHOTOCONTROLLER_H

#include "src/gphoto/camerahandler.h"
#include "src/gstreamer/gstreamercontroller.h"
#include "src/gui/widgetradiocontrol.h"
#include "src/streamers/camerastreamer.h"
#include "src/streamers/istreamer.h"
#include "src/streamers/picturestreamer.h"
#include <QList>
#include <QObject>
#include <QString>
#include <gphoto2/gphoto2-abilities-list.h>
#include <gphoto2/gphoto2-context.h>

class DSLRWebcam : public QObject {
  Q_OBJECT
public:
  DSLRWebcam();
  ~DSLRWebcam();

  QList<QPair<QString, QString>> getCameraList();
  QStringList getV4L2Devices();
  QStringList getCameraWidgets();

  WidgetRadioControl *createWidgetRadioControl(QWidget *parent,
                                               QString moniker);

  void startStream();
  void stopStream();

  void setV4L2Device(QString v4l2Device);

  void selectCamera(QString model, QString port);
  void startStreamOld();

  bool isStreamRunning();
  bool isStreamerRunning();

  void pauseStreamOld();
  void resumeStreamOld();

  void startCameraStreamer();
  void stopCameraStreamer();

  void useCameraStreamer();
  void usePictureStreamer();
  void killCurrentStreamer();

  void interruptCamera();
  void resumeCamera();

public slots:

  void toggleDOF(bool enable);

protected:
  GPContext *gphotoContext = NULL;
  CameraHandler *cameraHandler = NULL;

  GStreamerController *gstreamer = NULL;

  IStreamer *currentStreamer = NULL;
  CameraStreamer *cameraStreamer = NULL;
  PictureStreamer *pictureStreamer = NULL;

  QString v4l2Device;

  QString cameraModel;
  QString cameraPort;

  void deleteCameraHandler();
};

#endif
