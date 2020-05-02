#include "gphoto.h"
#include "integration.h"

GphotoContext::GphotoContext() { context = gp_context_new(); }
GphotoContext::~GphotoContext() { gp_context_unref(context); }

QList<QPair<QString, QString>> GphotoContext::getCameras() {
  return Gppp::getCameraList(context);
}
