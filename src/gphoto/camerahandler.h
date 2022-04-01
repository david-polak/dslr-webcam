#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <gphoto2/gphoto2-camera.h>

#include <QList>
#include <QPair>
#include <QString>

class CameraHandler {
public:
  CameraHandler(QString model, QString port, GPContext *context);
  ~CameraHandler();

  QStringList getWidgets(CameraWidgetType type, int readonly);
  CameraWidget *getWidget(const QString &moniker);

  Camera *camera;

  void setTrueDepthOfField(bool value);

  QString getWidgetValue(const QString &moniker);
  QStringList getWidgetValues(const QString &moniker);
  void setWidgetValue(const QString &moniker, const QString &value);

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
