#ifndef GPHOTOCONTEXT_H
#define GPHOTOCONTEXT_H

#include <QList>
#include <QString>
#include <gphoto2/gphoto2-abilities-list.h>
#include <gphoto2/gphoto2-context.h>

class GPhotoController {
public:
  GPhotoController();
  ~GPhotoController();

  QList<QPair<QString, QString>> getCameraList();

protected:
  GPContext *context;
  CameraAbilitiesList *abilities;
};

#endif // GPHOTOCONTEXT_H
