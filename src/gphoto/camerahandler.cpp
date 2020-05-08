#include "camerahandler.h"
#include "gphoto.h"

CameraHandler::CameraHandler(QString model, QString port, GPContext *context) {
  this->context = context;
  this->model = model;
  this->port = port;

  qDebug() << "CameraHandler(" << this->model << "," << this->port << ");";
  raise(gp_camera_new(&camera));

  initAbilitiesList();
  initPortInfoList();
  initPortInfo();
  initRootConfig();
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

void CameraHandler::initPortInfoList() {
  gp_port_info_list_new(&portInfoList);
  gp_port_info_list_load(portInfoList);
  gp_port_info_list_count(portInfoList);
}

void CameraHandler::initRootConfig() {
  const char *portData = port.toLocal8Bit().constData();
  raise(gp_camera_get_config(camera, &rootConfig, context));
}

void CameraHandler::initPortInfo() {
  int path = raise(gp_port_info_list_lookup_path(
      portInfoList, this->port.toLocal8Bit().constData()));

  GPPortInfo portInfo;
  raise(gp_port_info_list_get_info(portInfoList, path, &portInfo));
  raise(gp_camera_set_port_info(camera, portInfo));
}

CameraHandler::~CameraHandler() {
  qDebug() << "~CameraHandler()";
  if (portInfoList != NULL) {
    gp_port_info_list_free(portInfoList);
  }
  if (abilitiesList != NULL) {
    raise(gp_abilities_list_free(abilitiesList));
  }
  if (rootConfig != NULL) {
    raise(gp_widget_free(rootConfig));
  }
  if (camera != NULL) {
    raise(gp_camera_unref(camera));
  }
}
