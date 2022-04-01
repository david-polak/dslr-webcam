#include "Utils.h"
#include <QDebug>

QPair<QString, QString> Utils::findCamera(
    const QList<QPair<QString, QString>> &list, const QString &model) {
  for (const auto &item : list) {
    if (item.first == model) {
      return item;
    }
  }
  return {};
}
