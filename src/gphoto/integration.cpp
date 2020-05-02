#include "integration.h"

#include <QList>
#include <QPair>

int autodetect(CameraList *list, GPContext *context) {
  gp_list_reset(list);
  return gp_camera_autodetect(list, context);
}

// QList<QPair<QString, QString>> getCameraList(GPContext *context) {
//  const char *model;
//  const char *port;

//  CameraList *list;

//  gp_list_new(&list);

//  autodetect(list, context);

//  int i;
//  for (i = 0; i < gp_list_count(list); i++) {
//    gp_list_get_name(list, i, model);
//    gp_list_get_value(list, i, port);
//    // qStdout() << "item" <<endl;
//    //        if (!strcmp(*model, "Canon EOS 100D")) {
//    //            gp_list_free (list);
//    //            return 0;
//    //        }
//  }
//  gp_list_free(list);
//}
