#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "src/dslrwebcam.h"
#include "ui_mainwindow.h"
#include "widgetradiocontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void populateCameraList();
  void refreshBtnAction();
  void handleCameraListClick(const QModelIndex &index);

protected:
  QWidget *cameraTab;
  QWidget *settingsTab;
  QSettings settings;

  QList<QPair<QString, QString>> cameraList;

  void uiInitialSetup();
  void uiInitialiseSelectCameraTab();
  void uiPopulateCameraList();

public slots:

  void streamControlBtnAction();
  void cameraBtnAction();

  void changeCamera(int index);
  void pause();
  void resume();
  void useCamera();
  void usePicture();
  void fillCameraBox();
  void fillV4L2List();
  void setV4L2Device(int index);

  void addWidget();

protected:
  void closeEvent(QCloseEvent *event);
  void enableStreamers();
  void disableStreamers();

private:
  Ui::MainWindow *ui;
  DSLRWebcam *dslrWebcam;
  void selectCamera(int index);
};
#endif // MAINWINDOW_H
