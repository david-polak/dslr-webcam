#ifndef WIDGETRADIOCONTROL_H
#define WIDGETRADIOCONTROL_H

#include "src/dslrwebcam.h"
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
  WidgetRadioControl(DSLRWebcam *dslrWebcam, QString moniker);
  ~WidgetRadioControl() override;

protected:
  QString moniker;
  DSLRWebcam *dslrWebcam;

  void initialiseValues();

private slots:
  void handleValueChange(const QString &value);

private:
  Ui::WidgetRadioControl ui{};
};

#endif
