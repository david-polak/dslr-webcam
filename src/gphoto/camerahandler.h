#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <QString>
#include <gphoto2/gphoto2-camera.h>

class CameraHandler {
public:
  CameraHandler(const QString model, const QString port,
                CameraAbilitiesList *abilities);
  ~CameraHandler();
  void setPortInfo(GPPortInfo portInfo);

  // private:
  Camera *camera;
};

#endif // CAMERAHANDLER_H
