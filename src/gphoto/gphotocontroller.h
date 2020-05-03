#ifndef GPHOTOCONTROLLER_H
#define GPHOTOCONTROLLER_H

#include "camerahandler.h"
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
  GPContext *context;
  CameraAbilitiesList *abilities;
  CameraHandler *handler;
  GPPortInfoList *portinfolist = NULL;

  CameraStreamer *cameraStreamer;

  IStreamer *currentStreamer;
};

#endif
