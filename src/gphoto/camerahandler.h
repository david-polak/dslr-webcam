#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <QString>
#include <gphoto2/gphoto2-camera.h>

class CameraHandler {
public:
  CameraHandler(QString model, QString port, GPContext *context);
  ~CameraHandler();

  // private:
  Camera *camera;

protected:
  CameraAbilitiesList *abilitiesList = NULL;
  GPContext *context = NULL;
  CameraWidget *rootConfig = NULL;
  GPPortInfoList *portInfoList = NULL;

  QString model;
  QString port;

  void initAbilitiesList();
  void initPortInfoList();
  void initRootConfig();
  void initPortInfo();
};

#endif // CAMERAHANDLER_H
