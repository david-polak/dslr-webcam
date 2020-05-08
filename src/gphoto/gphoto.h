#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-context.h>

#include <QDebug>
#include <QList>
#include <QPair>
#include <QString>

namespace GPhoto {

QList<QPair<QString, QString>> getCameraList(GPContext *context);

} // namespace GPhoto

inline int raise(int returned) {
  if (returned < GP_OK) {
    qDebug() << "Error GPhoto returned: " << returned;
    throw returned;
  }
  return returned;
}