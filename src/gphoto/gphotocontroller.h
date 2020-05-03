#ifndef GPHOTOCONTROLLER_H
#define GPHOTOCONTROLLER_H

#include <QList>
#include <QString>
#include <gphoto2/gphoto2-abilities-list.h>
#include <gphoto2/gphoto2-context.h>

class GPhotoController {
public:
  GPhotoController();
  ~GPhotoController();

  QList<QPair<QString, QString>> getCameraList();

  void testCamera(QString model, QString port);

protected:
  GPContext *context;
  CameraAbilitiesList *abilities;
};

#endif
