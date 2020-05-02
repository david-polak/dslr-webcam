#include "gui/mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-context.h>
#include <gphoto2/gphoto2-file.h>
#include <gphoto2/gphoto2-filesys.h>
#include <gphoto2/gphoto2-list.h>
#include <gphoto2/gphoto2-port-info-list.h>
#include <gphoto2/gphoto2-setting.h>
#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>

#define CR(result)                                                             \
  {                                                                            \
    int __r = (result);                                                        \
    if (__r < 0)                                                               \
      return __r;                                                              \
  }

inline QTextStream &qStdout() {
  static QTextStream r{stdout};
  return r;
}

static GPPortInfoList *portinfolist = NULL;
static CameraAbilitiesList *abilities = NULL;

/*
 * This function opens a camera depending on the specified model and port.
 */
int sample_open_camera(Camera **camera, const char *model, const char *port,
                       GPContext *context) {
  int ret, m, p;
  CameraAbilities a;
  GPPortInfo pi;

  ret = gp_camera_new(camera);
  if (ret < GP_OK)
    return ret;

  if (!abilities) {
    /* Load all the camera drivers we have... */
    ret = gp_abilities_list_new(&abilities);
    if (ret < GP_OK)
      return ret;
    ret = gp_abilities_list_load(abilities, context);
    if (ret < GP_OK)
      return ret;
  }

  /* First lookup the model / driver */
  m = gp_abilities_list_lookup_model(abilities, model);
  if (m < GP_OK)
    return ret;
  ret = gp_abilities_list_get_abilities(abilities, m, &a);
  if (ret < GP_OK)
    return ret;
  ret = gp_camera_set_abilities(*camera, a);
  if (ret < GP_OK)
    return ret;

  if (!portinfolist) {
    /* Load all the port drivers we have... */
    ret = gp_port_info_list_new(&portinfolist);
    if (ret < GP_OK)
      return ret;
    ret = gp_port_info_list_load(portinfolist);
    if (ret < 0)
      return ret;
    ret = gp_port_info_list_count(portinfolist);
    if (ret < 0)
      return ret;
  }

  /* Then associate the camera with the specified port */
  p = gp_port_info_list_lookup_path(portinfolist, port);
  switch (p) {
  case GP_ERROR_UNKNOWN_PORT:
    fprintf(stderr,
            "The port you specified "
            "('%s') can not be found. Please "
            "specify one of the ports found by "
            "'gphoto2 --list-ports' and make "
            "sure the spelling is correct "
            "(i.e. with prefix 'serial:' or 'usb:').",
            port);
    break;
  default:
    break;
  }
  if (p < GP_OK)
    return p;

  ret = gp_port_info_list_get_info(portinfolist, p, &pi);
  if (ret < GP_OK)
    return ret;
  ret = gp_camera_set_port_info(*camera, pi);
  if (ret < GP_OK)
    return ret;
  return GP_OK;
}

int action_camera_capture_movie(Camera *camera, GPContext *context,
                                const char *arg) {
  CameraFile *file;
  int r;
  int fd;

  fd = dup(fileno(stdout));

  CR(gp_file_new_from_fd(&file, fd));

  while (1) {
    const char *mime;
    r = gp_camera_capture_preview(camera, file, context);
    if (r < 0) {
      qStdout() << "Movie capture error... Exiting.";
      break;
    }
    gp_file_get_mime_type(file, &mime);

    if (strcmp(mime, GP_MIME_JPEG)) {
      qStdout() << "Movie capture error... Unhandled MIME type";
      break;
    }
  }
  gp_file_unref(file);
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();

  // qStdout() << "start" <<endl;
  // int sample_autodetect (CameraList *list, GPContext *context) {

  //    GPContext * context = gp_context_new();
  //    int ret;
  //    ret = select_canon(&model, &port, context);
  //    qStdout() << ret << endl;
  //    qStdout() << model << endl;
  //    qStdout() << port << endl;

  //    qStdout() << "end" <<endl;
}
