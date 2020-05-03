#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-context.h>

#include <QList>
#include <QPair>
#include <QString>

namespace GPhoto {

QList<QPair<QString, QString>> getCameraList(GPContext *context);

void setCameraAbilities(Camera *camera, const char *model,
                        CameraAbilitiesList *abilities);

} // namespace GPhoto
