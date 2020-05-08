#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <QString>
#include <gphoto2/gphoto2-camera.h>

class CameraHandler {
public:
  CameraHandler(QString model, QString port, GPContext *context);
  ~CameraHandler();
  void setPortInfo(GPPortInfo portInfo);

  // private:
  Camera *camera;

protected:
  CameraAbilitiesList *abilitiesList = NULL;
  GPContext *context = NULL;

  QString model;
  QString port;

  void initAbilitiesList();
};

#endif // CAMERAHANDLER_H
