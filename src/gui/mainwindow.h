#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/gphoto/gphoto.h"
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
  GphotoContext *gphoto;
};
#endif // MAINWINDOW_H
