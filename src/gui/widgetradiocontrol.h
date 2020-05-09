#ifndef WIDGETRADIOCONTROL_H
#define WIDGETRADIOCONTROL_H

#include "gphoto2/gphoto2-widget.h"
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
  explicit WidgetRadioControl(QWidget *parent, QString moniker,
                              CameraWidget *widget);
  ~WidgetRadioControl();

private slots:

protected:
  void initChoices();
  CameraWidget *widget;
  QString moniker;

private:
  Ui::WidgetRadioControl ui;
};

#endif