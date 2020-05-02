#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->camera, SIGNAL(currentIndexChanged(int)), this,
          SLOT(changeCamera(int)));

  // QComboBox::addItem ( const QString & text, const QVariant & userData =
  // QVariant() )
  //    QComboBox * camera = ui->camera;
  //    camera->addItem("test", "data");
  //    camera->addItem("test2", "data2");
  //    camera->addItem("test3", "data3");
}

void MainWindow::changeCamera(int index) { qDebug() << index << endl; }

MainWindow::~MainWindow() { delete ui; }
