#include "mainwindow.h"

#include <QComboBox>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    dslrWebcam = new DSLRWebcam();

    fillCameraBox();

    connect(ui->streamControlBtn, SIGNAL(clicked()), this,
            SLOT(streamControlBtnAction()));

    connect(ui->cameraBtn, SIGNAL(clicked()), this, SLOT(cameraBtnAction()));
    connect(ui->refreshBtn, SIGNAL(clicked()), this, SLOT(fillCameraBox()));

    connect(ui->realAperture, SIGNAL(toggled(bool)), dslrWebcam,
            SLOT(toggleDOF(bool)));

    connect(ui->addWidgetBtn, SIGNAL(clicked()), this, SLOT(addWidget()));

    QTimer::singleShot(0, this, SLOT(fillV4L2List()));
}

void MainWindow::streamControlBtnAction() {
    if (dslrWebcam->isStreamRunning()) {
        dslrWebcam->stopStream();
        ui->streamControlBtn->setStyleSheet("");
        disableStreamers();
    } else {
        dslrWebcam->startStream();
        ui->streamControlBtn->setStyleSheet("background-color: #ffccd5;");
        enableStreamers();
    }
}

void MainWindow::enableStreamers() { ui->cameraBtn->setEnabled(true); }
void MainWindow::disableStreamers() { ui->cameraBtn->setEnabled(false); }

void MainWindow::cameraBtnAction() {
    if (dslrWebcam->isStreamerRunning()) {
        dslrWebcam->stopCameraStreamer();
    } else {
        dslrWebcam->startCameraStreamer();
    }
}

void MainWindow::addWidget() {
    QString name = ui->selectWidgetBox->currentText();
    ui->cameraVerticalLayout->addWidget(
        dslrWebcam->createWidgetRadioControl(this, name));
}

void MainWindow::fillV4L2List() {
    ui->outputDeviceList->clear();

    auto list = dslrWebcam->getV4L2Devices();
    if (list.empty()) {
        QString error = "Could not find any v4l2 devices.";
        error += " Please run `modprobe v4l2loopback exclusive_caps=1` to add "
                 "one.";
        QMessageBox::information(this, "Error", error, QMessageBox::Ok);
        QCoreApplication::exit(1);
    }

    // connecting here ensures signal gets triggered on addItems()
    connect(ui->outputDeviceList, SIGNAL(currentIndexChanged(int)), this,
            SLOT(setV4L2Device(int)));
    ui->outputDeviceList->addItems(list);
}

void MainWindow::setV4L2Device(int index) {
    QString device = ui->outputDeviceList->itemText(index);
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

    if (list.length() == 1) {
        ui->cameraBox->setCurrentIndex(1);
    }
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

    auto cameraWidgets = dslrWebcam->getCameraWidgets();
    ui->addWidgetBtn->setEnabled(true);
    ui->selectWidgetBox->clear();
    ui->selectWidgetBox->setEnabled(true);
    ui->selectWidgetBox->addItems(cameraWidgets);

    ui->cameraVerticalLayout->addWidget(
        dslrWebcam->createWidgetRadioControl(this, "Aperture"));
    ui->cameraVerticalLayout->addWidget(
        dslrWebcam->createWidgetRadioControl(this, "ISO Speed"));
    ui->cameraVerticalLayout->addWidget(
        dslrWebcam->createWidgetRadioControl(this, "Shutter Speed"));
}

void MainWindow::pause() { dslrWebcam->pauseStreamOld(); }
void MainWindow::resume() { dslrWebcam->resumeStreamOld(); }

void MainWindow::useCamera() { dslrWebcam->useCameraStreamer(); }
void MainWindow::usePicture() { dslrWebcam->usePictureStreamer(); }

void MainWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "MainWindow::closeEvent()";
    delete dslrWebcam;
}

MainWindow::~MainWindow() {
    qDebug() << "~MainWindow()";
    delete ui;
}
