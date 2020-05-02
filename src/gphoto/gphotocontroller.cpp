#include "gphotocontroller.h"
#include "gphoto.h"

GPhotoController::GPhotoController() {
  // TODO: handle return values
  context = gp_context_new();

  // loading abilities from libGPhoto2 camera drivers
  gp_abilities_list_new(&abilities);
  gp_abilities_list_load(abilities, context);
}

GPhotoController::~GPhotoController() {
  gp_abilities_list_free(abilities);
  gp_context_unref(context);
}

QList<QPair<QString, QString>> GPhotoController::getCameraList() {
  return GPhoto::getCameraList(context);
}
