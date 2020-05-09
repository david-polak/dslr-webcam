#include "widgetradiocontrol.h"

#include "src/gphoto/gphoto.h"
#include <QDebug>
#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-widget.h>

WidgetRadioControl::WidgetRadioControl(QWidget *parent, QString moniker,
                                       CameraWidget *widget)
    : QWidget(parent) {

  this->widget = widget;
  this->moniker = moniker;

  ui.setupUi(this);
  ui.widgetNameLbl->setText(moniker);

  initChoices();
}

void WidgetRadioControl::initChoices() {
  char *current;
  gp_raise(gp_widget_get_value(widget, &current));
  int count = gp_raise(gp_widget_count_choices(widget));

  for (int i = 0; i < count; i++) {
    const char *choice;
    gp_raise(gp_widget_get_choice(widget, i, &choice));
    ui.values->addItem(choice);
  }
  ui.values->setCurrentText(current);
}

WidgetRadioControl::~WidgetRadioControl() { qDebug() << "~WidgetRadioControl"; }
