#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QDebug>

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
  connect(ui->apertureUp, SIGNAL(clicked()), this, SLOT(apertureUp()));
  connect(ui->refreshBtn, SIGNAL(clicked()), this, SLOT(fillCameraBox()));
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
