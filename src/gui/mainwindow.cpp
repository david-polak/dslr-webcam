#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  gphotoController = new GPhotoController();

  connect(ui->cameraBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(changeCamera(int)));

  auto list = gphotoController->getCameraList();

  for (const auto &item : list) {
    ui->cameraBox->addItem(item.first, item.second);
  }
}
void MainWindow::changeCamera(int index) {
  QVariant data = ui->cameraBox->itemData(index);

  qDebug() << index << endl;
  qDebug() << data << endl;
}

MainWindow::~MainWindow() {
  delete gphotoController;
  delete ui;
}
