#include "addtimerdialog.h"
#include "ui_addtimerdialog.h"
#include "widgetsettings.h"

#include <QFile>

addTimerDialog::addTimerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTimerDialog)
{
    ui->setupUi(this);

    QFile file(":/stylesheet.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->setStyleSheet(file.readAll());
        file.close();
    }


    addSounds(ui->SoundBox);


    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->createButton, SIGNAL(clicked()), this, SLOT(returnAndClose()));

    // Validation for text field.
    QRegExp rx("[A-Z,a-z,0-9, ]{1,19}");
    QValidator *validator = new QRegExpValidator(rx, this);

    ui->timerName->setText("Timer");

    ui->timerName->setValidator(validator);

}

addTimerDialog::~addTimerDialog()
{
    delete ui;
}

void addTimerDialog::updateWidget(GlobalSettings _globalSettings)
{
    globalSettings = _globalSettings;

    ui->interval->setDisplayFormat(globalSettings.timerTimeFormat);
}

void addTimerDialog::returnAndClose()
{
    int elpasedTime = ui->interval->time().hour()*3600*1000+
            ui->interval->time().minute()*60*1000+
            ui->interval->time().second()*1000;

    QString timerName = ui->timerName->text();

    emit this->sendTimerData(WidgetSettings(elpasedTime, timerName,true, ui->SoundBox->itemData(ui->SoundBox->currentIndex()).toString()));

    this->close();
}
