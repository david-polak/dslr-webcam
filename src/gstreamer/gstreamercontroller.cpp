#include "gstreamercontroller.h"

#include <bits/stdc++.h>

#include <QDebug>
#include <QDir>

GStreamerController::GStreamerController() {
}

GStreamerController::~GStreamerController() {
  if (running) {
    stop();
  }
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
  if (running) {
    qDebug() << "GStreamerController is already streaming.";
    return;
  }

  QString command = "gst-launch-1.0 fdsrc";
  command += " ! decodebin3 name=dec";
  command += " ! queue";
  command += " ! videoconvert";
  command += " ! v4l2sink device=" + device;

  output = popen(command.toLocal8Bit().constData(), "w");
  fd = dup(fileno(output));
  running = true;
}

void GStreamerController::stop() {
  if (!running) {
    qDebug() << "GStreamerController is not streaming.";
    return;
  }
  fflush(output);
  close(fd);
  system("killall gst-launch-1.0"); // :P I'll deal with it later
  pclose(output);
  running = false;
}

int GStreamerController::getFd() {
  return fd;
}

void GStreamerController::setV4L2Device(QString device) {
  this->device = device;
}
