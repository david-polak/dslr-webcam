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
  void handleRefreshBtnClick();
  void handleCameraListClick(const QModelIndex &index);
  void handleUseCameraBtnClick();
  void handleRememberCameraCboxClick();
  void handleForgetCameraBtnClick();
  void handleOutputDeviceListChange(const int &index);
  void handleStartBtnClick();

  void verifyV4l2ListNotEmpty();

protected:
  QWidget *selectCameraTab;
  QWidget *cameraTab;
  QWidget *settingsTab;
  QSettings settings;

  QList<QPair<QString, QString>> cameraList;
  QPair<QString, QString> selectedCamera;
  QStringList v4l2List;
  QString v4l2Device;

  void populateCameraList();
  void populateV4l2List();
  void useCamera();

  void uiInitialSetup();
  void uiInitialiseSelectCameraTab();
  void uiPopulateCameraList();

  void uiInitialiseSettingsTab();
  void uiInitialiseCameraTab();
  void uiInitialiseOutputDeviceList();
  void uiInitialiseStartBtn();

  void deleteUiCameraListModel();

public slots:

  void streamControlBtnAction();
  void cameraBtnAction();

  void changeCamera(int index);
  void pause();
  void resume();
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
