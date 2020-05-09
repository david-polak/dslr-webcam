#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <QList>
#include <QPair>
#include <QString>
#include <gphoto2/gphoto2-camera.h>

class CameraHandler {
public:
  CameraHandler(QString model, QString port, GPContext *context);
  ~CameraHandler();

  // private:
  Camera *camera;

  QList<QString> getWidgets(CameraWidgetType type, int readonly);
  CameraWidget *getWidget(QString moniker);

protected:
  CameraAbilitiesList *abilitiesList = NULL;
  GPContext *context = NULL;
  CameraWidget *rootConfig = NULL;
  GPPortInfoList *portInfoList = NULL;
  QList<QPair<QString, CameraWidget *>> widgets;

  QString model;
  QString port;

  void initAbilitiesList();
  void initPortInfoList();
  void initRootConfig();
  void initPortInfo();
  void initWidgets();

private:
  void fillWidgetsDFS(CameraWidget *widget);
};

#endif // CAMERAHANDLER_H
