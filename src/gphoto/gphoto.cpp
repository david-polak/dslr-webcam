#include "gphoto.h"

#include <QPair>
#include <gphoto2/gphoto2-list.h>
#include <gphoto2/gphoto2-port-info-list.h>

int autodetect(CameraList *list, GPContext *context) {
  gp_list_reset(list);
  return gp_camera_autodetect(list, context);
}

QList<QPair<QString, QString>> GPhoto::getCameraList(GPContext *context) {
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

void GPhoto::setCameraAbilities(Camera *camera, const char *model,
                                CameraAbilitiesList *abilities) {
  CameraAbilities _abilitites;
  int _model;

  _model = gp_abilities_list_lookup_model(abilities, model);
  gp_abilities_list_get_abilities(abilities, _model, &_abilitites);
  gp_camera_set_abilities(camera, _abilitites);
}

//#include <gphoto2/gphoto2-camera.h>
//#include <gphoto2/gphoto2-context.h>
//#include <gphoto2/gphoto2-file.h>
//#include <gphoto2/gphoto2-filesys.h>
//#include <gphoto2/gphoto2-list.h>
//#include <gphoto2/gphoto2-port-info-list.h>
//#include <gphoto2/gphoto2-setting.h>

// inline QTextStream &qStdout() {
//  static QTextStream r{stdout};
//  return r;
//}
