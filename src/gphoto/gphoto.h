#ifndef CAMERA_H
#define CAMERA_H

#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-context.h>

#include <QMap>
#include <QString>

namespace GPhoto {
QList<QPair<QString, QString>> getCameraList(GPContext *context);
}

#endif // CAMERA_H
