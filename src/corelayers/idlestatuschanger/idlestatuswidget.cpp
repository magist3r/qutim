#include <libqutim/status.h>
#include <libqutim/config.h>
#include "idlestatuswidget.h"
#include "ui_idlestatuswidget.h"
#include "idle-global.h"
#include "idlestatuschanger.h"
#include "QMessageBox"

IdleStatusWidget::IdleStatusWidget() :
    ui(new Ui::IdleStatusWidget)
{
    ui->setupUi(this);
	 Status status;
	 status.setType(Status::Away);
	 ui->awayCheckBox->setText(ui->awayCheckBox->text().arg(status.name().toString()));
	 status.setType(Status::NA);
	 ui->naCheckBox->setText(ui->naCheckBox->text().arg(status.name().toString()));
}

IdleStatusWidget::~IdleStatusWidget()
{
    delete ui;
}

void IdleStatusWidget::loadImpl()
{
	Config conf = Config(AA_CONFIG_GROUP);
	ui->awayCheckBox->setChecked(conf.value("away-enabled", true));
	ui->naCheckBox->  setChecked(conf.value("na-enabled",   true));
	ui->awaySpinBox->setValue(conf.value("away-secs", AWAY_DEF_SECS)/60);
	ui->naSpinBox->  setValue(conf.value("na-secs",   NA_DEF_SECS)/60);
	ui->awayTextBox->setText(conf.value("away-text", ""));
	ui->naTextBox->  setText(conf.value("na-text",   ""));
	lookForWidgetState(ui->awayCheckBox);
	lookForWidgetState(ui->naCheckBox);
	lookForWidgetState(ui->awaySpinBox);
	lookForWidgetState(ui->naSpinBox);
	lookForWidgetState(ui->awayTextBox);
	lookForWidgetState(ui->naTextBox);
}

void IdleStatusWidget::saveImpl()
{
	Config conf = Config(AA_CONFIG_GROUP);
	conf.setValue("away-enabled", ui->awayCheckBox->isChecked());
	conf.setValue("na-enabled",   ui->naCheckBox->  isChecked());
	conf.setValue("away-secs", ui->awaySpinBox->value()*60);
	conf.setValue("na-secs",   ui->naSpinBox->  value()*60);
	conf.setValue("away-text", ui->awayTextBox->toPlainText());
	conf.setValue("na-text",   ui->naTextBox->  toPlainText());
	conf.sync();
	pIdleStatusChanger->reloadSettings();
}

void IdleStatusWidget::cancelImpl()
{

}

void IdleStatusWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
