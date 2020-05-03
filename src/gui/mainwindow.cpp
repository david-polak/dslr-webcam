#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  gphotoController = new GPhotoController();

  fillCameraBox();

  connect(ui->pauseBtn, SIGNAL(clicked()), this, SLOT(pause()));
}

void MainWindow::fillCameraBox() {
  disconnect(ui->cameraBox, SIGNAL(currentIndexChanged(int)), this,
             SLOT(changeCamera(int)));

  ui->cameraBox->clear();
  ui->cameraBox->addItem("disconnected", false);

  auto list = gphotoController->getCameraList();
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

  qDebug() << "model:" << model << " port:" << port << endl;

  gphotoController->selectCamera(model, port);
  gphotoController->useCameraStreamer();
  gphotoController->startStream();
}

void MainWindow::pause() { gphotoController->pauseStream(); }

MainWindow::~MainWindow() {
  delete gphotoController;
  delete ui;
}
