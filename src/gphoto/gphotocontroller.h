#ifndef GPHOTOCONTROLLER_H
#define GPHOTOCONTROLLER_H

#include "camerahandler.h"
#include "src/gstreamer/gstreamercontroller.h"
#include "src/streamers/camerastreamer.h"
#include "src/streamers/istreamer.h"
#include <QList>
#include <QString>
#include <gphoto2/gphoto2-abilities-list.h>
#include <gphoto2/gphoto2-context.h>

class GPhotoController {
public:
  GPhotoController();
  ~GPhotoController();

  QList<QPair<QString, QString>> getCameraList();

  void selectCamera(QString model, QString port);
  void startStream();

  bool isStreamRunning();

  void pauseStream();
  void resumeStream();

  void useCameraStreamer();

protected:
  GPContext *context = NULL;
  CameraAbilitiesList *abilities = NULL;
  CameraHandler *handler = NULL;
  GPPortInfoList *portinfolist = NULL;

  GStreamerController *gstreamer = NULL;

  IStreamer *currentStreamer = NULL;
  CameraStreamer *cameraStreamer = NULL;
};

#endif
