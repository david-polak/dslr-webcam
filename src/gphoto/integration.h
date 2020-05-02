#ifndef CAMERA_H
#define CAMERA_H

#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-context.h>
#include <gphoto2/gphoto2-list.h>
#include <gphoto2/gphoto2-port-info-list.h>

int autodetect(CameraList *list, GPContext *context);

#endif // CAMERA_H
