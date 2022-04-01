#include "widgetradiocontrol.h"
#include "src/gphoto/gphoto.h"
#include <QDebug>

WidgetRadioControl::WidgetRadioControl(DSLRWebcam *dslrWebcam, QString moniker)
    : QWidget() {

  this->dslrWebcam = dslrWebcam;
  this->moniker = moniker;

  ui.setupUi(this);
  ui.widgetNameLbl->setText(moniker);

  this->initialiseValues();
  connect(
      ui.values,
      SIGNAL(currentTextChanged(QString)),
      this,
      SLOT(handleValueChange(QString)));
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

void WidgetRadioControl::handleValueChange(const QString &value) {
  this->dslrWebcam->setWidgetValue(this->moniker, value);
}
