#ifndef DSLR_WEBCAM_UTILS_H
#define DSLR_WEBCAM_UTILS_H

#include <QList>
#include <QMainWindow>
#include <QPair>
#include <QSettings>
#include <QString>

class Utils {
public:
  static QPair<QString, QString>
  findCamera(const QList<QPair<QString, QString>> &list, const QString &model);
};

#endif // DSLR_WEBCAM_UTILS_H
