#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->cameraBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(changeCamera(int)));

  // QComboBox::addItem ( const QString & text, const QVariant & userData =
  // QVariant() )
  //    QComboBox * camera = ui->camera;
  ui->cameraBox->addItem("test1", "data");
  ui->cameraBox->addItem("test2", "data2");
  ui->cameraBox->addItem("test3", "data3");
}

void MainWindow::changeCamera(int index) {
  QVariant data = ui->cameraBox->itemData(index);

  qDebug() << index << endl;
  qDebug() << data << endl;
}

MainWindow::~MainWindow() { delete ui; }
