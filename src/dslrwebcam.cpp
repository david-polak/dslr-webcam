#include "dslrwebcam.h"
#include "gphoto/camerahandler.h"
#include "gphoto/gphoto.h"

#include "src/gstreamer/gstreamercontroller.h"
#include <QDebug>
#include <gphoto2/gphoto2-port-info-list.h>

DSLRWebcam::DSLRWebcam() {
  // TODO: handle return values
  context = gp_context_new();
}

DSLRWebcam::~DSLRWebcam() {
  qDebug() << "~dslrWebcam()";

  if (cameraStreamer) {
    cameraStreamer->requestInterruption();
    cameraStreamer->wait();
    delete cameraStreamer;
    qDebug() << "delete cameraStreamer;";
  }
  // TODO: cleanup streamers

  if (gstreamer) {
    delete gstreamer;
  }

  if (handler) {
    delete handler;
  }

  gp_context_unref(context);
}

QList<QPair<QString, QString>> DSLRWebcam::getCameraList() {
  return GPhoto::getCameraList(context);
}

void DSLRWebcam::selectCamera(QString model, QString port) {
  handler = new CameraHandler(model, port, context);
  //handler->getWidgets();
}

void DSLRWebcam::killCurrentStreamer() {
  if (currentStreamer) {
    currentStreamer->requestInterruption();
    currentStreamer->wait();
    delete currentStreamer;
  }
}

void DSLRWebcam::useCameraStreamer() {
  killCurrentStreamer();
  cameraStreamer = new CameraStreamer();
  cameraStreamer->setCameraHandler(handler);
  cameraStreamer->setContext(context);
  currentStreamer = cameraStreamer;

  int fd = gstreamer->getFd();
  currentStreamer->setFd(fd);
  currentStreamer->start();
}

void DSLRWebcam::usePictureStreamer() {
  killCurrentStreamer();
  pictureStreamer = new PictureStreamer();
  pictureStreamer->setImagePath(
      "/home/david/Data/Code/dslr-webcam/images/blank.jpg");
  currentStreamer = pictureStreamer;

  int fd = gstreamer->getFd();
  currentStreamer->setFd(fd);
  currentStreamer->start();
}

void DSLRWebcam::startStream() {
  gstreamer = new GStreamerController();
  gstreamer->start();
}
bool DSLRWebcam::isStreamRunning() { return true; }
void DSLRWebcam::pauseStream() {
  qDebug() << "pause stream";
  cameraStreamer->requestInterruption();
}

void DSLRWebcam::resumeStream() {
  qDebug() << "resume stream";
  cameraStreamer->start();
}

void DSLRWebcam::apertureUp() {
  qDebug() << "apertureUP()";
  //   /main/capturesettings/aperture
  // Label: Aperture
  // Readonly: 0
  // Type: RADIO
  // Current: 2.8
  // Choice: 0 2.8
  // Choice: 1 3.2
  // Choice: 2 3.5
  // Choice: 3 4
  // Choice: 4 4.5
  // Choice: 5 5
  // Choice: 6 5.6
  // Choice: 7 6.3
  // Choice: 8 7.1
  // Choice: 9 8
  // Choice: 10 9
  // Choice: 11 10
  // Choice: 12 11
  // Choice: 13 13
  // Choice: 14 14
  // Choice: 15 16
  // Choice: 16 18
  // Choice: 17 20
  // Choice: 18 22
  // END

  //   const char *value = "16";

  //   CameraWidget *rootconfig, *child;
  //   int ret, ro;
  //   CameraWidgetType type;

  //   ret = _find_widget_by_name(p, name, &child, &rootconfig);
  //   if (ret != GP_OK)
  //     return ret;

  //   int cnt, i;
  //   char *endptr;

  //   cnt = gp_widget_count_choices(child);
  //   if (cnt < GP_OK)
  //   {
  //     ret = cnt;
  //     return;
  //   }
  //   ret = GP_ERROR_BAD_PARAMETERS;
  //   for (i = 0; i < cnt; i++)
  //   {
  //     const char *choice;

  //     ret = gp_widget_get_choice(child, i, &choice);
  //     if (ret != GP_OK)
  //       continue;
  //     if (!strcmp(choice, value))
  //     {
  //       ret = gp_widget_set_value(child, value);
  //       return;
  //     }
  //   }
  //   if (i != cnt)
  //     return;

  //   /* make sure we parse just 1 integer, and there is nothing more.
  // 		 * sscanf just does not provide this, we need strtol.
  // 		 */
  //   i = strtol(value, &endptr, 10);
  //   if ((value != endptr) && (*endptr == '\0'))
  //   {
  //     if ((i >= 0) && (i < cnt))
  //     {
  //       const char *choice;

  //       ret = gp_widget_get_choice(child, i, &choice);
  //       if (ret == GP_OK)
  //         ret = gp_widget_set_value(child, choice);
  //       return;
  //     }
  //   }
  //   /* Lets just try setting the value directly, in case we have flexible
  //   setters,
  // 		 * like PTP shutterspeed. */
  //   ret = gp_widget_set_value(child, value);
  //   if (ret == GP_OK)
  //     return;
  // }
}
