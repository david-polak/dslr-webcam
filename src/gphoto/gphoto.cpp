#include "gphoto.h"

#include <gphoto2/gphoto2-list.h>

#include <QPair>

int autodetect(CameraList *list, GPContext *context) {
  gp_raise(gp_list_reset(list));
  return gp_raise(gp_camera_autodetect(list, context));
}

QList<QPair<QString, QString>> GPhoto::getCameraList(GPContext *context) {
  QList<QPair<QString, QString>> result;
  CameraList *list;
  gp_raise(gp_list_new(&list));
  autodetect(list, context);

  const char *model;
  const char *port;

  for (int i = 0; i < gp_list_count(list); i++) {
    gp_raise(gp_list_get_name(list, i, &model));
    gp_raise(gp_list_get_value(list, i, &port));
    result.append(QPair<QString, QString>(model, port));
  }

  gp_raise(gp_list_free(list));
  return result;
}

GPContext *GPhoto::createContext() {
  return gp_context_new();
}

void GPhoto::deleteContext(GPContext *context) {
  gp_context_unref(context);
}
