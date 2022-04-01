#include "widgetradiocontrol.h"

//#include <gphoto2/gphoto2-camera.h>
//#include <gphoto2/gphoto2-widget.h>

#include <QDebug>

#include "src/gphoto/gphoto.h"

WidgetRadioControl::WidgetRadioControl(DSLRWebcam *dslrWebcam, QString moniker)
    : QWidget() {

  this->dslrWebcam = dslrWebcam;
  this->moniker = moniker;

  ui.setupUi(this);
  ui.widgetNameLbl->setText(moniker);

  this->initialiseValues();

  //  this->cameraHandler = cameraHandler;
  //  gp_raise(gp_widget_get_name(widget, &name));
  //
  //  initialiseValues();
  //
  //  connect(
  //      ui.values,
  //      SIGNAL(currentTextChanged(QString)),
  //      this,
  //      SLOT(changeOption(QString)));
}

WidgetRadioControl::~WidgetRadioControl() {
  qDebug() << "~WidgetRadioControl";
}

void WidgetRadioControl::initialiseValues() {
  const auto values = this->dslrWebcam->getWidgetValues(this->moniker);
  const auto value = this->dslrWebcam->getWidgetValue(this->moniker);
  this->ui.values->addItems(values);
  this->ui.values->setCurrentText(value);
}

//    ui.values->addItem(choice);

//  qDebug() << value;

//  char *current;
//  gp_raise(gp_widget_get_value(widget, &current));
//  int count = gp_raise(gp_widget_count_choices(widget));
//
//  for (int i = 0; i < count; i++) {
//    const char *choice;
//    gp_raise(gp_widget_get_choice(widget, i, &choice));
//    ui.values->addItem(choice);
//  }
//  ui.values->setCurrentText(current);
//}
//
// void WidgetRadioControl::changeOption(QString option) {
//   //  qDebug() << "Set" << name << "=" << option;
//   //  gp_raise(gp_widget_set_value(widget,
//   option.toLocal8Bit().constData()));
//   //
//   //  cameraHandler->interruptCamera();
//   //  gp_raise(gp_camera_set_single_config(
//   //      cameraHandler->camera, name, widget, context));
//   //  cameraHandler->resumeCamera();
// }
