#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/dslrwebcam.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void changeCamera(int index);
  void start();
  void pause();
  void resume();
  void useCamera();
  void usePicture();
  void apertureUp();

protected:
  void fillCameraBox();
  void closeEvent(QCloseEvent *event);

private:
  Ui::MainWindow *ui;
  DSLRWebcam *dslrWebcam;
};
#endif // MAINWINDOW_H
