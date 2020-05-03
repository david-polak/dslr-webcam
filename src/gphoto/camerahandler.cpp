#include "camerahandler.h"
#include "gphoto.h"

CameraHandler::CameraHandler(const QString model, const QString port,
                             CameraAbilitiesList *abilities) {
  gp_camera_new(&camera);
  const char *modelData = model.toLocal8Bit().constData();
  GPhoto::setCameraAbilities(camera, modelData, abilities);
}

void CameraHandler::setPortInfo(GPPortInfo portInfo) {
  gp_camera_set_port_info(camera, portInfo);
}

CameraHandler::~CameraHandler() { gp_camera_unref(camera); }
