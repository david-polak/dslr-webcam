#ifndef WIDGETRADIOCONTROL_H
#define WIDGETRADIOCONTROL_H

#include "gphoto2/gphoto2-widget.h"
#include "src/gphoto/camerahandler.h"
#include "ui_widgetradiocontrol.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class WidgetRadioControl;
}
QT_END_NAMESPACE

typedef void (*InterruptCamera)(void);
typedef void (*ResumeCamera)();

class WidgetRadioControl : public QWidget {
  Q_OBJECT

public:
  explicit WidgetRadioControl(QWidget *parent, QString moniker,
                              CameraHandler *cameraHandler, GPContext *context,
                              CameraWidget *widget);

  ~WidgetRadioControl();

private slots:
  void changeOption(QString option);

protected:
  void initChoices();

  QString moniker;
  CameraWidget *widget = NULL;
  GPContext *context = NULL;
  CameraHandler *cameraHandler = NULL;

  const char *name;

private:
  Ui::WidgetRadioControl ui;
};

#endif
