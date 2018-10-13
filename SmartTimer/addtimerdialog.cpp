#include "addtimerdialog.h"
#include "ui_addtimerdialog.h"

addTimerDialog::addTimerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTimerDialog)
{
    ui->setupUi(this);

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

void addTimerDialog::returnAndClose()
{
    int elpasedTime = ui->interval->time().hour()*3600*1000+
            ui->interval->time().minute()*60*1000+
            ui->interval->time().second()*1000;

    QString timerName = ui->timerName->text();

    emit this->sendTimerData(elpasedTime, timerName);

    this->close();
}