#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/gphoto/gphotocontroller.h"
#include <QMainWindow>

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
  void changeCamera(int index);

private:
  Ui::MainWindow *ui;
  GPhotoController *gphotoController;
};
#endif // MAINWINDOW_H
