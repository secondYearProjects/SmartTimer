#include "changealarmdialog.h"
#include "ui_changealarmdialog.h"
#include "alertwidget.h"

ChangeAlarmDialog::ChangeAlarmDialog(alertwidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeAlarmDialog)
{
    ui->setupUi(this);

     ui->alarmName->setText(parent->getName());
     ui->time->setTime(QTime::fromMSecsSinceStartOfDay(parent->getAlertTime()));

     connect(ui->changeButton,SIGNAL(clicked()), this, SLOT(changeAlarm()));
}

ChangeAlarmDialog::~ChangeAlarmDialog()
{
    delete ui;


}

void ChangeAlarmDialog::changeAlarm()
{
    emit changeAlarmSignal(getMsecs(ui->time->time()), ui->alarmName->text());

    this->close();
}
