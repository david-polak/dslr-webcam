#include "mainwindow.h"

#include <QComboBox>
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include <QStringListModel>
#include <QTimer>

#include "src/Utils.h"
#include "ui_mainwindow.h"
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  this->ui->setupUi(this);
  this->dslrWebcam = new DSLRWebcam();

  this->uiInitialSetup();

  this->populateV4l2List();
  this->uiInitialiseOutputDeviceList();

  this->populateCameraList();

  QString cameraSetting = settings.value("camera", "").toString();
  this->selectedCamera = Utils::findCamera(this->cameraList, cameraSetting);

  if (this->selectedCamera.second != "") {
    this->useCamera();
  } else {
    this->uiInitialiseSelectCameraTab();
  }

  QTimer::singleShot(0, this, SLOT(verifyV4l2ListNotEmpty()));
}

MainWindow::~MainWindow() {
  qDebug() << "~MainWindow()";
  this->deleteWidgetRadioControls();
  this->deleteUiCameraListModel();
  delete this->selectCameraTab;
  delete this->ui;
  delete this->dslrWebcam;
}

void MainWindow::uiInitialSetup() {
  this->ui->startBtn->setVisible(false);

  this->settingsTab = this->ui->settingsTab;
  this->cameraTab = this->ui->cameraTab;

  this->ui->tabs->removeTab(1);
  this->ui->tabs->removeTab(1);
}

void MainWindow::populateCameraList() {
  this->cameraList = this->dslrWebcam->getCameraList();
}

void MainWindow::populateV4l2List() {
  this->v4l2List = DSLRWebcam::getV4L2Devices();
}

void MainWindow::verifyV4l2ListNotEmpty() {
  if (this->v4l2List.empty()) {
    QString error = "Could not find any v4l2 devices."
                    " Please run `modprobe v4l2loopback exclusive_caps=1`.";
    QMessageBox::information(this, "Error", error, QMessageBox::Ok);
    QCoreApplication::exit(1);
  }
}

void MainWindow::deleteUiCameraListModel() {
  auto currentModel = this->ui->cameraList->model();
  if (currentModel != nullptr) {
    this->ui->cameraList->setModel(nullptr);
    delete currentModel;
  }
}

void MainWindow::uiPopulateCameraList() {
  this->deleteUiCameraListModel();

  QStringList cameraModelList;
  cameraModelList << "None";
  for (const auto &item : this->cameraList) {
    cameraModelList << item.first;
  }

  auto *model = new QStringListModel();
  model->setStringList(cameraModelList);
  this->ui->cameraList->setModel(model);
}

void MainWindow::uiInitialiseSelectCameraTab() {
  this->uiPopulateCameraList();
  connect(
      this->ui->refreshBtn,
      SIGNAL(clicked()),
      this,
      SLOT(handleRefreshBtnClick()));
  connect(
      ui->cameraList,
      SIGNAL(clicked(QModelIndex)),
      this,
      SLOT(handleCameraListClick(QModelIndex)));
  connect(
      ui->useCameraBtn,
      SIGNAL(clicked()),
      this,
      SLOT(handleUseCameraBtnClick()));
  connect(
      ui->rememberCameraCbox,
      SIGNAL(clicked()),
      this,
      SLOT(handleRememberCameraCboxClick()));
  connect(
      ui->realAperture,
      SIGNAL(toggled(bool)),
      dslrWebcam,
      SLOT(handleRealApertureChange(bool)));
}

void MainWindow::handleRefreshBtnClick() {
  this->populateCameraList();
  this->uiPopulateCameraList();
  this->ui->useCameraBtn->setEnabled(false);
  this->ui->rememberCameraCbox->setEnabled(false);
}

void MainWindow::handleCameraListClick(const QModelIndex &index) {
  auto selectedModel = index.data().toString();
  this->selectedCamera = Utils::findCamera(this->cameraList, selectedModel);

  if (this->selectedCamera.second == "") {
    this->ui->useCameraBtn->setEnabled(false);
    this->ui->rememberCameraCbox->setEnabled(false);
    return;
  }
  this->ui->useCameraBtn->setEnabled(true);
  this->ui->rememberCameraCbox->setEnabled(true);
}

void MainWindow::handleUseCameraBtnClick() {
  this->useCamera();
}

void MainWindow::useCamera() {
  if (this->selectedCamera.second == "") {
    qCritical() << "No port found for selectedCamera "
                << this->selectedCamera.first;
    return;
  }
  this->dslrWebcam->setCamera(this->selectedCamera);

  this->uiInitialiseStartBtn();

  this->uiInitialiseCameraTab();
  this->ui->tabs->addTab(this->cameraTab, "Camera");

  this->uiInitialiseSettingsTab();
  this->ui->tabs->addTab(this->settingsTab, "Settings");

  this->selectCameraTab = this->ui->selectCameraTab;
  this->ui->tabs->removeTab(0);
}

void MainWindow::handleRememberCameraCboxClick() {
  if (this->ui->rememberCameraCbox->checkState() == Qt::Checked) {
    settings.setValue("camera", this->selectedCamera.first);
  } else {
    settings.setValue("camera", "");
  }
}

void MainWindow::uiInitialiseSettingsTab() {
  auto cameraSetting = settings.value("camera", "");
  if (cameraSetting == "") {
    ui->selectedCameraLabel->setVisible(false);
    ui->forgetCameraBtn->setVisible(false);
  } else {
    ui->selectedCameraLabel->setVisible(true);
    ui->forgetCameraBtn->setVisible(true);
    ui->forgetCameraBtn->setText("Forget " + cameraSetting.toString());
    connect(
        this->ui->forgetCameraBtn,
        SIGNAL(clicked()),
        this,
        SLOT(handleForgetCameraBtnClick()));
  }
}

void MainWindow::handleForgetCameraBtnClick() {
  ui->forgetCameraBtn->setEnabled(false);
  ui->forgetCameraBtn->setText("Camera forgotten");
  settings.setValue("camera", "");
}

void MainWindow::uiInitialiseOutputDeviceList() {
  connect(
      ui->outputDeviceList,
      SIGNAL(currentIndexChanged(int)),
      this,
      SLOT(handleOutputDeviceListChange(int)));
  ui->outputDeviceList->addItems(this->v4l2List);
}

void MainWindow::handleOutputDeviceListChange(const int &index) {
  this->v4l2Device = ui->outputDeviceList->itemText(index);
  this->dslrWebcam->setV4l2Device(this->v4l2Device);
}

void MainWindow::uiInitialiseCameraTab() {
  auto cameraWidgets = this->dslrWebcam->getCameraWidgets();

  ui->addWidgetBtn->setEnabled(true);
  ui->selectWidgetBox->clear();
  ui->selectWidgetBox->setEnabled(true);
  ui->selectWidgetBox->addItems(cameraWidgets);
  connect(
      ui->addWidgetBtn,
      SIGNAL(clicked()),
      this,
      SLOT(handleAddWidgetBtnClick()));

  this->uiCreateWidgetRadioControl("Aperture");
  this->uiCreateWidgetRadioControl("ISO Speed");
  this->uiCreateWidgetRadioControl("Shutter Speed");
}

void MainWindow::uiInitialiseStartBtn() {
  connect(ui->startBtn, SIGNAL(clicked()), this, SLOT(handleStartBtnClick()));
  ui->startBtn->setVisible(true);
}

void MainWindow::handleStartBtnClick() {
  if (this->dslrWebcam->isRunning()) {
    this->dslrWebcam->stop();
    this->ui->startBtn->setStyleSheet("");
    this->ui->startBtn->setText("Start Webcam");
  } else {
    this->dslrWebcam->start();
    this->ui->startBtn->setStyleSheet("background-color: #ffccd5;");
    this->ui->startBtn->setText("Stop Webcam");
    this->ui->outputDeviceList->setEnabled(false);
  }
}

void MainWindow::handleAddWidgetBtnClick() {
  QString moniker = ui->selectWidgetBox->currentText();
  this->uiCreateWidgetRadioControl(moniker);
}

void MainWindow::uiCreateWidgetRadioControl(const QString &moniker) {
  auto *widget = new WidgetRadioControl(this->dslrWebcam, moniker);
  this->widgetRadioControlList.append(widget);
  this->ui->controlWidgetLayout->addWidget(widget);
}

void MainWindow::deleteWidgetRadioControls() {
  for (auto &widget : this->widgetRadioControlList) {
    delete widget;
  }
}

void MainWindow::handleRealApertureChange(bool value) {
  this->dslrWebcam->setTrueDepthOfField(value);
}
