#include "Utils.h"
#include <QDebug>

QPair<QString, QString>
Utils::findCamera(QList<QPair<QString, QString>> *list, QString model) {
  for (const auto &item : *list) {
    if (item.first == model) {
      return item;
    }
  }
  return {};
}
