#include "gui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QCoreApplication::setOrganizationName("david-polak");
  QCoreApplication::setOrganizationDomain("polakdavid.com");
  QCoreApplication::setApplicationName("dslr-webcam");

  QApplication a(argc, argv);
  MainWindow mainWindow;
  mainWindow.show();
  return a.exec();
}
