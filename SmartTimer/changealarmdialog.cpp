#include "changealarmdialog.h"
#include "ui_changealarmdialog.h"
#include "alertwidget.h"

#include <QFile>

ChangeAlarmDialog::ChangeAlarmDialog(alertwidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeAlarmDialog)
{
    ui->setupUi(this);

    WidgetSettings alarmSettings = parent->getSettings();

    addSounds(ui->SoundBox);

    QFile file(":/stylesheet.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->setStyleSheet(file.readAll());
        file.close();
    }
    ui->alarmName->setText(alarmSettings.name);
    ui->time->setTime(QTime::fromMSecsSinceStartOfDay(parent->getAlertTime()));
    ui->SoundBox->setCurrentIndex(ui->SoundBox->findData(QVariant(alarmSettings.signalPath)));

    connect(ui->changeButton,SIGNAL(clicked()), this, SLOT(changeAlarm()));
    connect(ui->cancelButton,SIGNAL(clicked()), this, SLOT(close()));
}

ChangeAlarmDialog::~ChangeAlarmDialog()
{
    delete ui;


}

void ChangeAlarmDialog::updateWidget(GlobalSettings _globalSettings)
{
    globalSettings = std::move(_globalSettings);

    ui->time->setDisplayFormat(globalSettings.alarmTimeFormat);
}

void ChangeAlarmDialog::changeAlarm()
{
    emit changeAlarmSignal(WidgetSettings(getMsecs(ui->time->time()), ui->alarmName->text(),true,ui->SoundBox->itemData(ui->SoundBox->currentIndex()).toString()));

    this->close();
}
