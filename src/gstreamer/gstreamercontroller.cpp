#include "gstreamercontroller.h"
#include <bits/stdc++.h>

GStreamerController::GStreamerController() {}

GStreamerController::~GStreamerController() {
  if (output) {
    stop();
  }
}

void GStreamerController::start() {
  output = popen("gst-launch-1.0 fdsrc ! decodebin3 name=dec ! queue "
                 "! videoconvert ! v4l2sink device=/dev/video2",
                 "w");

  fd = dup(fileno(output));
}

void GStreamerController::stop() {
  fflush(output);
  close(fd);
  system("killall gst-launch-1.0"); // :P I'll deal with it later
  pclose(output);
}

int GStreamerController::getFd() { return fd; }
