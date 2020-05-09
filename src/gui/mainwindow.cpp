#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QDebug>

#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  dslrWebcam = new DSLRWebcam();

  fillCameraBox();

  connect(ui->pauseBtn, SIGNAL(clicked()), this, SLOT(pause()));
  connect(ui->resumeBtn, SIGNAL(clicked()), this, SLOT(resume()));

  connect(ui->cameraBtn, SIGNAL(clicked()), this, SLOT(useCamera()));
  connect(ui->pictureBtn, SIGNAL(clicked()), this, SLOT(usePicture()));
  connect(ui->startBtn, SIGNAL(clicked()), this, SLOT(start()));
  connect(ui->refreshBtn, SIGNAL(clicked()), this, SLOT(fillCameraBox()));

  QTimer::singleShot(0, this, SLOT(fillV4L2List()));
}

void MainWindow::fillV4L2List() {
  ui->v4l2List->clear();

  auto list = dslrWebcam->getV4L2Devices();
  if (list.empty()) {
    QString error = "Could not find any v4l2 devices.";
    error += " Please run `modprobe v4l2loopback exclusive_caps=1` to add one.";
    QMessageBox::information(this, "Error", error, QMessageBox::Ok);
    QCoreApplication::exit(1);
  }

  // connecting here ensures signal gets triggered on addItems()
  connect(ui->v4l2List, SIGNAL(currentIndexChanged(int)), this,
          SLOT(setV4L2Device(int)));
  ui->v4l2List->addItems(list);
}

void MainWindow::setV4L2Device(int index) {
  QString device = ui->v4l2List->itemText(index);
  dslrWebcam->setV4L2Device(device);
}

void MainWindow::fillCameraBox() {
  disconnect(ui->cameraBox, SIGNAL(currentIndexChanged(int)), this,
             SLOT(changeCamera(int)));

  ui->cameraBox->clear();
  ui->cameraBox->addItem("disconnected", false);

  auto list = dslrWebcam->getCameraList();
  for (const auto &item : list) {

    ui->cameraBox->addItem(item.first, item.second);
  }

  connect(ui->cameraBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(changeCamera(int)));
}

void MainWindow::changeCamera(int index) {
  QVariant data = ui->cameraBox->itemData(index);

  if (data.type() == QVariant::Bool) {
    return;
  }

  QString model = ui->cameraBox->currentText();
  QString port = data.value<QString>();

  qDebug() << "model:" << model << " port:" << port;

  dslrWebcam->selectCamera(model, port);
}

void MainWindow::start() { dslrWebcam->startStream(); }
void MainWindow::pause() { dslrWebcam->pauseStream(); }
void MainWindow::resume() { dslrWebcam->resumeStream(); }

void MainWindow::useCamera() { dslrWebcam->useCameraStreamer(); }
void MainWindow::usePicture() { dslrWebcam->usePictureStreamer(); }
void MainWindow::apertureUp() { dslrWebcam->apertureUp(); }

void MainWindow::closeEvent(QCloseEvent *event) {
  qDebug() << "MainWindow::closeEvent()";
  delete dslrWebcam;
}

MainWindow::~MainWindow() {
  qDebug() << "~MainWindow()";
  delete ui;
}
