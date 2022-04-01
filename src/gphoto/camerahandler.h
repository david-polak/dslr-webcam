#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <gphoto2/gphoto2-camera.h>

#include <QList>
#include <QPair>
#include <QString>

#include "src/streamers/camerastreamer.h"

class CameraHandler {
public:
  CameraHandler(QString model, QString port, GPContext *context);
  ~CameraHandler();

  QStringList getWidgets(CameraWidgetType type, int readonly);
  CameraWidget *getWidget(const QString &moniker);

  Camera *camera;

  void setCameraStreamer(CameraStreamer *streamer);
  void toggleDOF(bool enable);
  void interruptCamera();
  void resumeCamera();

  void setWidgetValue(QString name, QString value);

  QString getWidgetValue(const QString &moniker);
  QStringList getWidgetValues(const QString &moniker);

protected:
  CameraAbilitiesList *abilitiesList = NULL;
  GPContext *context = NULL;
  CameraWidget *rootConfig = NULL;
  CameraStreamer *streamer = NULL;
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
