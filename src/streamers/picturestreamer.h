#ifndef PICTURESTREAMER_H
#define PICTURESTREAMER_H

#include "istreamer.h"
#include "src/gphoto/camerahandler.h"
#include <QImage>

class PictureStreamer : public IStreamer {
public:
  ~PictureStreamer();
  void run() override;
  void setFd(int fd) override;

  void setImagePath(QString path);

private:
  QImage *image;
};

#endif // STREAM_H
