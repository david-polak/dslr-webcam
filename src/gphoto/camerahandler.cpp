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
  initWidgets();
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

void CameraHandler::initWidgets() {
  fillWidgetsDFS(rootConfig);
  qDebug() << "Camera widgets count:" << widgets.size();
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

void CameraHandler::fillWidgetsDFS(CameraWidget *widget) {
  const char *label;
  const char *name;
  raise(gp_widget_get_label(widget, &label));
  raise(gp_widget_get_name(widget, &name));

  const char *moniker;
  if (strlen(label)) {
    moniker = label;
  } else {
    moniker = name;
  }

  widgets.append(QPair<QString, CameraWidget *>(moniker, widget));

  int childrenCount = gp_widget_count_children(widget);
  for (int i = 0; i < childrenCount; i++) {
    CameraWidget *child;
    raise(gp_widget_get_child(widget, i, &child));
    fillWidgetsDFS(child);
  }
}

QList<QString> CameraHandler::getWidgets(CameraWidgetType type, int readonly) {
  QList<QString> result;

  for (auto pair : widgets) {
    CameraWidget *widget = pair.second;

    CameraWidgetType _type;
    int _readonly;

    raise(gp_widget_get_type(widget, &_type));
    raise(gp_widget_get_readonly(widget, &_readonly));

    if (_type == type && _readonly == readonly) {
      result.append(pair.first);
    }
  }

  return result;
}
