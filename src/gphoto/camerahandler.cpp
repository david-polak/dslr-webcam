#include "camerahandler.h"
#include "gphoto.h"

CameraHandler::CameraHandler(QString model, QString port, GPContext *context) {
  this->context = context;
  this->model = model;
  this->port = port;

  qDebug() << "CameraHandler(" << this->model << "," << this->port << ");";

  gp_camera_new(&camera);
  // GPhoto::setCameraAbilities(camera, modelData, abilities);

  initAbilitiesList();
}

void CameraHandler::initAbilitiesList() {
  // loading abilities from libGPhoto2 camera drivers
  raise(gp_abilities_list_new(&abilitiesList));
  raise(gp_abilities_list_load(abilitiesList, context));

  CameraAbilities abilitites;
  int index = raise(gp_abilities_list_lookup_model(
      abilitiesList, this->model.toLocal8Bit().constData()));
  raise(gp_abilities_list_get_abilities(abilitiesList, index, &abilitites));
  raise(gp_camera_set_abilities(camera, abilitites));
}

void CameraHandler::setPortInfo(GPPortInfo portInfo) {
  gp_camera_set_port_info(camera, portInfo);
}

CameraHandler::~CameraHandler() {
  qDebug() << "~CameraHandler()";
  gp_abilities_list_free(abilitiesList);
  gp_camera_unref(camera);
}
