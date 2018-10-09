#include "changetimerdialog.h"
#include "ui_changetimerdialog.h"

#include <QTime>

ChangeTimerDialog::ChangeTimerDialog(TimerWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeTimerDialog)
{
    ui->setupUi(this);

    par = parent;

    ui->timerName->setText(parent->getTimerName());
    ui->interval->setTime(QTime::fromMSecsSinceStartOfDay(parent->getTimerDuration()));

    connect(ui->changeButton, SIGNAL(clicked()), this, SLOT(changeTimerAndQuit()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
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
