#include "changetimerdialog.h"
#include "ui_changetimerdialog.h"

#include <QTime>
#include <QFile>

ChangeTimerDialog::ChangeTimerDialog(TimerWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeTimerDialog)
{
    ui->setupUi(this);

    QFile file(":/stylesheet.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->setStyleSheet(file.readAll());
        file.close();
    }


    par = parent;

    ui->timerName->setText(parent->getTimerName());
    ui->interval->setTime(QTime::fromMSecsSinceStartOfDay(parent->getTimerDuration()));

    connect(ui->changeButton, SIGNAL(clicked()), this, SLOT(changeTimerAndQuit()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    // Validation for text field.
    QRegExp rx("[A-Z,a-z,0-9, ]{1,19}");
    QValidator *validator = new QRegExpValidator(rx, this);

    ui->timerName->setValidator(validator);
}

ChangeTimerDialog::~ChangeTimerDialog()
{
    delete ui;
}

void ChangeTimerDialog::changeTimerAndQuit()
{
    int elpasedTime = ui->interval->time().hour()*3600*1000+
            ui->interval->time().minute()*60*1000+
            ui->interval->time().second()*1000;

    par->setTimerDuration(elpasedTime);
    par->setTimerName(ui->timerName->text());

    this->close();
}
