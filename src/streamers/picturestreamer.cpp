#include "picturestreamer.h"

#include "unistd.h"

#include <fstream>
#include <iostream>

PictureStreamer::~PictureStreamer() {}

void PictureStreamer::run() {
  const void *buf = image.data();
  size_t size = image.size();

  qDebug() << buf << " " << size;

  forever {
    if (this->isInterruptionRequested()) {
      qDebug() << "Interruption requested";
      return;
    }
    write(this->fd, buf, size);
    this->msleep(500);
  }
}
void PictureStreamer::setFd(int fd) { this->fd = fd; }
void PictureStreamer::setImagePath(QString path) {
  qDebug() << path;
  const char *pathData = path.toLocal8Bit().constData();

  std::ifstream ifs(pathData, std::ios::binary | std::ios::ate);
  std::ifstream::pos_type pos = ifs.tellg();
  std::vector<char> result(pos);

  ifs.seekg(0, std::ios::beg);
  ifs.read(&result[0], pos);

  image = result;

  qDebug() << result.size();
}