#include "addalarmdialog.h"
#include "ui_addalarmdialog.h"
#include "widgetsettings.h"

#include <QFile>





addAlarmDialog::addAlarmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addAlarmDialog)
{
    ui->setupUi(this);

    addSounds(ui->SoundBox);

    QFile file(":/stylesheet.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->setStyleSheet(file.readAll());
        file.close();
    }

    connect(ui->createButton,SIGNAL(clicked()),this,SLOT(sendData()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->alarmTime,SIGNAL(timeChanged(QTime)),this,SLOT(updateTimeTo(QTime)));
    updateTimeTo(ui->alarmTime->time());
}

addAlarmDialog::~addAlarmDialog()
{
    delete ui;
}

void addAlarmDialog::updateWidget(GlobalSettings _globalSettings)
{
    globalSettings = std::move(_globalSettings);
    ui->alarmTime->setDisplayFormat(globalSettings.alarmTimeFormat);
}

void addAlarmDialog::sendData()
{
    emit sendAlarmData(WidgetSettings(getMsecs(ui->alarmTime->time()),ui->alarmName->text(),true,ui->SoundBox->itemData(ui->SoundBox->currentIndex()).toString()));
    this->close();
}

void addAlarmDialog::updateTimeTo(QTime time)
{
    ui->toAlarmLabel->setText(QTime::fromMSecsSinceStartOfDay(calculateDuration(time)).toString(globalSettings.alarmTimeFormat));
}
