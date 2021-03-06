#include "gstreamercontroller.h"
#include <bits/stdc++.h>

#include <QDebug>
#include <QDir>

GStreamerController::GStreamerController() {}

GStreamerController::~GStreamerController() {
  if (output != NULL) {
    stop();
  }
}

void GStreamerController::start() {
  QString command = "gst-launch-1.0 fdsrc";
  command += " ! decodebin3 name=dec";
  command += " ! queue";
  command += " ! videoconvert";
  command += " ! v4l2sink device=" + device;

  output = popen(command.toLocal8Bit().constData(), "w");
  fd = dup(fileno(output));
}

void GStreamerController::stop() {
  fflush(output);
  close(fd);
  system("killall gst-launch-1.0"); // :P I'll deal with it later
  pclose(output);
}

int GStreamerController::getFd() { return fd; }

void GStreamerController::setV4L2Device(QString device) {
  this->device = device;
}

QStringList GStreamerController::listV4L2Devices() {
  QStringList output;
  qDebug() << "listV4L2Devices()";

  // TODO: use v4l2-ctl for write capability detection
  QStringList filters;
  filters << "video*";
  QDir dir("/dev");
  QFileInfoList files = dir.entryInfoList(filters, QDir::System);

  for (auto file : files) {
    output.append(file.filePath());
  }
  return output;
}