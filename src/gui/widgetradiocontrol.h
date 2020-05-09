#ifndef WIDGETRADIOCONTROL_H
#define WIDGETRADIOCONTROL_H

#include "ui_widgetradiocontrol.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class WidgetRadioControl;
}
QT_END_NAMESPACE

class WidgetRadioControl : public QWidget {
  Q_OBJECT

public:
  explicit WidgetRadioControl(QWidget *parent = nullptr);

private slots:

private:
  Ui::WidgetRadioControl ui;
};

#endif