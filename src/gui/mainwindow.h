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
  void handleAddWidgetBtnClick();
  void handleRealApertureChange(bool value);

  void verifyV4l2ListNotEmpty();

protected:
  DSLRWebcam *dslrWebcam;
  QWidget *selectCameraTab;
  QWidget *cameraTab;
  QWidget *settingsTab;
  QSettings settings;

  QList<QPair<QString, QString>> cameraList;
  QPair<QString, QString> selectedCamera;
  QList<WidgetRadioControl *> widgetRadioControlList;
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
  void deleteWidgetRadioControls();

  void uiCreateWidgetRadioControl(const QString &moniker);

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
