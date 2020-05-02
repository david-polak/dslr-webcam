#include "integration.h"

#include <QPair>
#include <gphoto2/gphoto2-list.h>
#include <gphoto2/gphoto2-port-info-list.h>

int autodetect(CameraList *list, GPContext *context) {
  gp_list_reset(list);
  return gp_camera_autodetect(list, context);
}

QList<QPair<QString, QString>> Gppp::getCameraList(GPContext *context) {
  QList<QPair<QString, QString>> result;
  CameraList *list;
  gp_list_new(&list);
  autodetect(list, context);

  const char *model;
  const char *port;

  for (int i = 0; i < gp_list_count(list); i++) {
    gp_list_get_name(list, i, &model);
    gp_list_get_value(list, i, &port);
    result.append(QPair<QString, QString>(model, port));
  }

  gp_list_free(list);
  return result;
}
