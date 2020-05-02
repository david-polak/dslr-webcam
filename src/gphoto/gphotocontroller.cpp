#include "gphotocontroller.h"
#include "gphoto.h"

GPhotoController::GPhotoController() { context = gp_context_new(); }
GPhotoController::~GPhotoController() { gp_context_unref(context); }

QList<QPair<QString, QString>> GPhotoController::getCameraList() {
  return GPhoto::getCameraList(context);
}
