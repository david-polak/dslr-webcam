#include "gstreamercontroller.h"

#include <QDebug>
#include <QDir>

GStreamerController::GStreamerController() {
}

GStreamerController::~GStreamerController() {
}

QStringList GStreamerController::getV4l2Devices() {
  QStringList list;
  // TODO: use v4l2-ctl for write capability detection
  QStringList filters;
  filters << "video*";
  QDir dir("/dev");
  QFileInfoList files = dir.entryInfoList(filters, QDir::System);
  for (const auto &file : files) {
    list.append(file.filePath());
  }
  return list;
}

void GStreamerController::start() {
  QString command = "gst-launch-1.0 fdsrc";
  command += " ! decodebin3 name=dec";
  command += " ! queue";
  command += " ! videoconvert";
  command += " ! v4l2sink device=" + device;

  outpipe = popen(command.toLocal8Bit().constData(), "w");
  fd = dup(fileno(outpipe));
}

void GStreamerController::stop() {
  fflush(outpipe);
  close(fd);

  // TODO: Figure out a proper solution...
  system("killall gst-launch-1.0");
  pclose(outpipe);
}

int GStreamerController::getFd() const {
  return fd;
}

void GStreamerController::setV4L2Device(QString v4l2Device) {
  this->device = v4l2Device;
}
