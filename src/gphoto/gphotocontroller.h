#ifndef GPHOTOCONTEXT_H
#define GPHOTOCONTEXT_H

#include <QList>
#include <QString>
#include <gphoto2/gphoto2-context.h>

class GPhotoController {
public:
  GPhotoController();
  ~GPhotoController();

  QList<QPair<QString, QString>> getCameraList();

protected:
  GPContext *context;
};

#endif // GPHOTOCONTEXT_H
