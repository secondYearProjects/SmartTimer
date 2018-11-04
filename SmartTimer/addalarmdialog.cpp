#include "addalarmdialog.h"
#include "ui_addalarmdialog.h"

#include <QFile>


static int getMsecs(const QTime& t)
{
    return (t.hour()*3600+t.minute()*60+t.second())*1000;
}

addAlarmDialog::addAlarmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addAlarmDialog)
{
    ui->setupUi(this);

    QFile file(":/stylesheet.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->setStyleSheet(file.readAll());
        file.close();
    }

    connect(ui->createButton,SIGNAL(clicked()),this,SLOT(sendData()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(close()));
}

addAlarmDialog::~addAlarmDialog()
{
    delete ui;
}

void addAlarmDialog::sendData()
{
    emit sendAlarmData(WidgetSettings(getMsecs(ui->alarmTime->time()),ui->alarmName->text(),true));
    this->close();
}
