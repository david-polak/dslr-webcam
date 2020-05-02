#ifndef GPHOTOCONTEXT_H
#define GPHOTOCONTEXT_H

#include <QList>
#include <QString>
#include <gphoto2/gphoto2-context.h>

class GphotoContext {
public:
  GphotoContext();
  ~GphotoContext();

  QList<QPair<QString, QString>> getCameras();

protected:
  GPContext *context;
};

#endif // GPHOTOCONTEXT_H
