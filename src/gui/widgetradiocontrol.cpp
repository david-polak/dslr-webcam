#include "widgetradiocontrol.h"

#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-widget.h>

#include <QDebug>

#include "src/gphoto/gphoto.h"

WidgetRadioControl::WidgetRadioControl(QWidget *parent, QString moniker,
                                       CameraHandler *cameraHandler,
                                       GPContext *context, CameraWidget *widget)

    : QWidget(parent) {
    this->widget = widget;
    this->moniker = moniker;
    this->context = context;
    this->cameraHandler = cameraHandler;

    ui.setupUi(this);
    ui.widgetNameLbl->setText(moniker);

    gp_raise(gp_widget_get_name(widget, &name));

    initChoices();

    connect(ui.values, SIGNAL(currentTextChanged(QString)), this,
            SLOT(changeOption(QString)));
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

void WidgetRadioControl::changeOption(QString option) {
    qDebug() << "Set" << name << "=" << option;
    gp_raise(gp_widget_set_value(widget, option.toLocal8Bit().constData()));

    cameraHandler->interruptCamera();
    gp_raise(gp_camera_set_single_config(cameraHandler->camera, name, widget,
                                         context));
    cameraHandler->resumeCamera();
}

WidgetRadioControl::~WidgetRadioControl() { qDebug() << "~WidgetRadioControl"; }
