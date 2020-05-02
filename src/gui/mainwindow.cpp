#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  gphoto = new GphotoContext();

  connect(ui->cameraBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(changeCamera(int)));

  auto list = gphoto->getCameras();

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
  delete gphoto;
  delete ui;
}
