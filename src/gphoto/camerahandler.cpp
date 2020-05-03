#include "camerahandler.h"
#include "gphoto.h"

CameraHandler::CameraHandler(const QString model, const QString port,
                             CameraAbilitiesList *abilities) {
  gp_camera_new(&camera);
  const char *modelData = model.toLocal8Bit().constData();
  GPhoto::setCameraAbilities(camera, modelData, abilities);
}

CameraHandler::~CameraHandler() { gp_camera_free(camera); }
