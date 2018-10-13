#include "alertwidget.h"
#include "ui_alertwidget.h"

#include <iostream>

alertwidget::alertwidget(int msecs, const QString& name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alertwidget)
{
    alertName = name;
    alertTime = QTime::fromMSecsSinceStartOfDay(msecs);
    state = false;
    blinking = false;

    ui->setupUi(this);

    ui->timeLabel->setText(alertTime.toString("hh:mm"));
    ui->alarmNameLabel->setText(alertName);

    ui->alertSwitch->setStatus(state);

    connect(ui->alertSwitch, SIGNAL(statusChanged(bool)),this, SLOT(statusChanged(bool)));
    connect(&alertTick, SIGNAL(timeout()), this, SLOT(onTickCheck()));
}

alertwidget::~alertwidget()
{
    delete ui;
}

int alertwidget::getAlertTime()
{
    return alertTime.elapsed()/1000;
}

void alertwidget::statusChanged(bool stat)
{
    state = stat;
    if (stat)
        alertTick.start(1000);
    else
    {
        alertTick.stop();
        blinkTimer.stop();
        blinking = false;
    }
}

void alertwidget::onTickCheck()
{
    //TODO: here
    if (QTime::currentTime() == alertTime)
    {
        std::cout << "!alert!" << std::endl;
        alertTick.stop();
        blinkTimer.stop();
        blinking = false;
    }
    else
        std::cout << "tick" << std::endl;
}
