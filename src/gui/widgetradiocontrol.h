#ifndef WIDGETRADIOCONTROL_H
#define WIDGETRADIOCONTROL_H

#include <QWidget>

//#include "gphoto2/gphoto2-widget.h"
//#include "src/gphoto/camerahandler.h"

#include "src/dslrwebcam.h"
#include "ui_widgetradiocontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class WidgetRadioControl;
}
QT_END_NAMESPACE

// typedef void (*InterruptCamera)(void);
// typedef void (*ResumeCamera)();

class WidgetRadioControl : public QWidget {
  Q_OBJECT

public:
  WidgetRadioControl(QWidget *parent, DSLRWebcam *dslrWebcam, QString moniker);
  ~WidgetRadioControl();

protected:
  QString moniker;
  DSLRWebcam *dslrWebcam;

private slots:
  //  void changeOption(QString option);

  //  void initChoices();

  //  CameraWidget *widget = NULL;
  //  GPContext *context = NULL;
  //  CameraHandler *cameraHandler = NULL;

  //  const char *name;

private:
  Ui::WidgetRadioControl ui;
};

#endif
