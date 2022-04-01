#include "camerahandler.h"

#include "gphoto.h"

CameraHandler::CameraHandler(QString model, QString port, GPContext *context) {
  this->context = context;
  this->model = model;
  this->port = port;

  qDebug() << "CameraHandler(" << this->model << "," << this->port << ");";
  gp_raise(gp_camera_new(&camera));

  initAbilitiesList();
  initPortInfoList();
  initPortInfo();
  initRootConfig();
  initWidgets();
}

void CameraHandler::initAbilitiesList() {
  // loading abilities from libGPhoto2 camera drivers
  gp_raise(gp_abilities_list_new(&abilitiesList));
  gp_raise(gp_abilities_list_load(abilitiesList, context));

  CameraAbilities abilities;
  int index = gp_raise(gp_abilities_list_lookup_model(
      abilitiesList, this->model.toLocal8Bit().constData()));
  gp_raise(gp_abilities_list_get_abilities(abilitiesList, index, &abilities));
  gp_raise(gp_camera_set_abilities(camera, abilities));
}

void CameraHandler::initPortInfoList() {
  gp_port_info_list_new(&portInfoList);
  gp_port_info_list_load(portInfoList);
  gp_port_info_list_count(portInfoList);
}

void CameraHandler::initRootConfig() {
  const char *portData = port.toLocal8Bit().constData();
  gp_raise(gp_camera_get_config(camera, &rootConfig, context));
}

void CameraHandler::initPortInfo() {
  int path = gp_raise(gp_port_info_list_lookup_path(
      portInfoList, this->port.toLocal8Bit().constData()));

  GPPortInfo portInfo;
  gp_raise(gp_port_info_list_get_info(portInfoList, path, &portInfo));
  gp_raise(gp_camera_set_port_info(camera, portInfo));
}

void CameraHandler::toggleDOF(bool enable) {
  interruptCamera();
  if (enable) {
    setWidgetValue("Depth of Field", "2");
  } else {
    setWidgetValue("Depth of Field", "0");
  }
  resumeCamera();
}

void CameraHandler::setWidgetValue(QString name, QString value) {
  for (auto pair : widgets) {
    if (pair.first == name) {
      auto _widget = pair.second;

      const char *name;
      gp_raise(gp_widget_get_name(_widget, &name));
      gp_raise(gp_widget_set_value(_widget, value.toLocal8Bit().constData()));
      gp_raise(gp_camera_set_single_config(camera, name, _widget, context));

      qDebug() << "Set" << name << "=" << value;
    }
  }
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
    gp_raise(gp_abilities_list_free(abilitiesList));
  }
  if (rootConfig != NULL) {
    gp_raise(gp_widget_free(rootConfig));
  }
  if (camera != NULL) {
    gp_raise(gp_camera_unref(camera));
  }
}

void CameraHandler::fillWidgetsDFS(CameraWidget *widget) {
  const char *label;
  const char *name;
  gp_raise(gp_widget_get_label(widget, &label));
  gp_raise(gp_widget_get_name(widget, &name));

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
    gp_raise(gp_widget_get_child(widget, i, &child));
    fillWidgetsDFS(child);
  }
}

QStringList CameraHandler::getWidgets(CameraWidgetType type, int readonly) {
  QStringList result;

  for (auto pair : widgets) {
    CameraWidget *widget = pair.second;

    CameraWidgetType _type;
    int _readonly;

    gp_raise(gp_widget_get_type(widget, &_type));
    gp_raise(gp_widget_get_readonly(widget, &_readonly));

    if (_type == type && _readonly == readonly) {
      result.append(pair.first);
    }
  }

  return result;
}

CameraWidget *CameraHandler::getWidget(const QString &moniker) {
  for (auto pair : widgets) {
    if (pair.first == moniker) {
      return pair.second;
    }
  }
  throw GP_ERROR;
}

QString CameraHandler::getWidgetValue(const QString &moniker) {
  char *value;
  gp_raise(gp_widget_get_value(this->getWidget(moniker), &value));
  return {value};
}

QStringList CameraHandler::getWidgetValues(const QString &moniker) {
  QStringList list;
  auto *widget = this->getWidget(moniker);
  int count = gp_raise(gp_widget_count_choices(widget));
  for (int i = 0; i < count; ++i) {
    const char *choice;
    gp_raise(gp_widget_get_choice(widget, i, &choice));
    list.append(QString(choice));
  }
  return list;
}

//  char *current;
//  int count = gp_raise(gp_widget_count_choices(widget));
//
//  for (int i = 0; i < count; i++) {
//    const char *choice;
//    gp_raise(gp_widget_get_choice(widget, i, &choice));
//    ui.values->addItem(choice);
//  }
//  ui.values->setCurrentText(current);

void CameraHandler::setCameraStreamer(CameraStreamer *streamer) {
  this->streamer = streamer;
}

void CameraHandler::interruptCamera() {
  qDebug() << "interruptCamera";
  if (streamer != NULL) {
    streamer->requestInterruption();
    streamer->wait();
  }
}

void CameraHandler::resumeCamera() {
  qDebug() << "resumeCamera";
  if (streamer != NULL) {
    streamer->start();
  }
}
