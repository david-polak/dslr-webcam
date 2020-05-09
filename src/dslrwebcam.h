#ifndef GPHOTOCONTROLLER_H
#define GPHOTOCONTROLLER_H

#include "src/gphoto/camerahandler.h"
#include "src/gstreamer/gstreamercontroller.h"
#include "src/gui/widgetradiocontrol.h"
#include "src/streamers/camerastreamer.h"
#include "src/streamers/istreamer.h"
#include "src/streamers/picturestreamer.h"
#include <QList>
#include <QString>
#include <gphoto2/gphoto2-abilities-list.h>
#include <gphoto2/gphoto2-context.h>

class DSLRWebcam {
public:
  DSLRWebcam();
  ~DSLRWebcam();

  QList<QPair<QString, QString>> getCameraList();
  QStringList getV4L2Devices();
  QStringList getCameraWidgets();

  WidgetRadioControl *createWidgetRadioControl(QWidget *parent,
                                               QString moniker);

  void setV4L2Device(QString device);

  void selectCamera(QString model, QString port);
  void startStream();

  bool isStreamRunning();

  void pauseStream();
  void resumeStream();

  void useCameraStreamer();
  void usePictureStreamer();

  void apertureUp();

public slots:

protected:
  GPContext *context = NULL;
  CameraHandler *handler = NULL;

  GStreamerController *gstreamer = NULL;

  IStreamer *currentStreamer = NULL;
  CameraStreamer *cameraStreamer = NULL;
  PictureStreamer *pictureStreamer = NULL;

  void killCurrentStreamer();
};

#endif
