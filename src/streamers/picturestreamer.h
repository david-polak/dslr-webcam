#ifndef PICTURESTREAMER_H
#define PICTURESTREAMER_H

#include <QImage>

#include "istreamer.h"
#include "src/gphoto/camerahandler.h"

class PictureStreamer : public IStreamer {
public:
  ~PictureStreamer();
  void run() override;
  void setFd(int fd) override;

  void setImagePath(QString path);

private:
  int fd;
  std::vector<char> image;
};

#endif // STREAM_H
